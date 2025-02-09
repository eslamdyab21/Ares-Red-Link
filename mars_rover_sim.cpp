#include <string>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>

#include "mars-rover/rover.h"
#include "network/comms_manager.h"
#include "ephemeris/ephemeris_data.h"


void delayedTransmitter(CommsManager *CommsManager, const std::string& ip, int port) {
    CommsManager->delayedTransmitter(ip, port);
}


int main() {
    EphemerisData EphemerisData;
    CommsManager CommsManager;
    Rover Rover;

    // Get signal delay from ephemeris
    // std::string mars_ephemeris_file = "source-data/mars2020.csv";
    // std::string sun_ephemeris_file  = "source-data/sun2020.csv";


    // EphemerisData.loadMarsEphemeris(mars_ephemeris_file);
    // const std::vector<EphemerisEntry>& mars_ephemeris_data = EphemerisData.getMarsEphemerisData();

    // EphemerisData.loadSunEphemeris(sun_ephemeris_file);
    // const std::vector<EphemerisEntry>& sun_ephemeris_data = EphemerisData.getSunEphemerisData();

    std::thread transmitterThread(delayedTransmitter, &CommsManager, "127.0.0.1", 8080);


    std::string file_name = "source-data/rover-sensors/WE__0019___________CAL_ENG_________________P01.CSV";
    std::ifstream file(file_name);

    std::string line;
    double signal_delay = 5;  // Delay in seconds
    while (Rover.readSensorData(file, line)) {
        // CommsManager.computeSignalDelay()
        Rover.sendSensorData(line, signal_delay);
        queueCond.notify_one();
        std::this_thread::sleep_for(std::chrono::seconds(1)); // Maintain real-time pacing
    }

}