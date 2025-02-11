# Ares-Red-Link

# Data Source 
![](images/astropixels_website.png)

We use the ephemeris data available in the  `astropixels` website, this website has recorded historical data for planets in our solar system from 2011.

A _geocentric ephemeris_ is a table that gives the celestial coordinates of an astronomical object over a range of times as seen from Earth's center.

We will be interested in the data window between 2020 to 2024.

<br/>

## Prepare Data
Inside the root directory of the project a python script `astro_ephemeris_data_parser.py` which takes two arguments:
1. `astro_object_type`: can be planets or sun
2. `astro_object_name`: can be sun, mars, earth, .....
3. `year`, the year of which want to analyse
![](images/prepare_data.png)


<br/>
<br/>
<br/>

# Delayed Mars Rover Sensors Data Simulation
Here we simulate sending data from Mars to Earth with the calculated light speed signal delay in real-time, the source sensors data frequency is each one second, and we send this data each one second too.

If a delay is `120s`, data from `T=0s` is sent at `T=120s`, data from `T=1s` is sent at `T=121s`, and so on.


<br/>

## Data Source 
![](images/mars_rover_sensors_data.png)
This data from mars is taken from The Planetary Atmospheres Node (ATM) of the Planetary Data System (PDS) https://pds-atmospheres.nmsu.edu/


<br/>

## Simulation
Two essential components are used here:
	1. `UDP` communication (simulating the Mars-Earth two ends)
	2. `Multi-threading` in Mars side to account for the light speed signal delay in real-time data sending

### Mars side
We send the rover sensors data here, we use the same two `EphemerisData` and `CommsManager` classes to calculate the light speed signal delay for the current day.

One more function `delayedTransmitter` is added to the `CommsManager` class to send the data with `UDP`, it runs in a separate thread and accounts for the signal delay.

```cpp
while (true) {
	std::unique_lock<std::mutex> lock(queueMutex);
	queueCond.wait(lock, [] { return !sensorsDataQueue.empty(); });
	
	if (!sensorsDataQueue.empty()) {
		DataPacket packet = sensorsDataQueue.front();
		auto now = std::chrono::steady_clock::now();		
		
		if (now >= packet.sendTime) {
			sensorsDataQueue.pop();
			lock.unlock();
			sendto(sock, packet.data.c_str(), packet.data.size(), 0, 
                   (struct sockaddr*)&serverAddr, sizeof(serverAddr));
			lock.lock();
		
		} else {
			queueCond.wait_until(lock, packet.sendTime);
		}
		
	}
}
```

It checks the queue **without blocking** and sends each packet at the exact **scheduled** time when a `queueCond.notify_one()` is called in the main flow.

The main flow of Mars side:
```cpp
int main() {

	EphemerisData EphemerisData;
	CommsManager CommsManager;
	Rover Rover;

	// UDP thread transmitter	
	std::thread transmitterThread(delayedTransmitter, &CommsManager,
	                              "127.0.0.1", 8080);  
	
	// Get signal delay from ephemeris
	.
	.
	.
  
	
	double signal_delay = 0; // Delay in seconds	
	signal_delay = CommsManager.computeSignalDelay(mars_ephemeris_data, sun_ephemeris_data);
	
	
	// Sending sensors data each one second
	std::string line;
	std::string file_name = "source-data/roversensors/WE__0019___________CAL_ENG_________________P01.CSV";
	
	std::ifstream file(file_name);
	
	while (Rover.readSensorData(file, line) && signal_delay != -1) {
		Rover.sendSensorData(line, signal_delay);;
		queueCond.notify_one();
		std::this_thread::sleep_for(std::chrono::seconds(1)); // Maintain real-time pacing
	}

}
```


### Earth side
We receive the sent sensors data by Mars, Earth side is the `server` side here and `Mars` is the `client` side in `UDP` terminology.
