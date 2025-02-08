#include <iostream>
#include <vector>
#include "ephemeris/ephemeris_data.h"
#include "network/comms_manager.h"

int main() {
    EphemerisData EphemerisData;
    CommsManager CommsManager;

    std::string mars_ephemeris_file = "source-data/mars2020.csv";
    std::string sun_ephemeris_file  = "source-data/sun2020.csv";


    EphemerisData.loadMarsEphemeris(mars_ephemeris_file);
    const std::vector<EphemerisEntry>& mars_ephemeris_data = EphemerisData.getMarsEphemerisData();

    EphemerisData.loadSunEphemeris(sun_ephemeris_file);
    const std::vector<EphemerisEntry>& sun_ephemeris_data = EphemerisData.getSunEphemerisData();



    int size = mars_ephemeris_data.size();
    double signal_delay;
    for (int i = 0; i < size; i++)
    {
        signal_delay = CommsManager.computeSignalDelay(mars_ephemeris_data[i], sun_ephemeris_data[i]);

        std::cout << "Date: " << mars_ephemeris_data[i].date
                  << ", RA: " << mars_ephemeris_data[i].ra
                  << ", Dec: " << mars_ephemeris_data[i].declination
                  << ", Distance (AU): " << mars_ephemeris_data[i].distance_au    
                  << ", Delay: " << signal_delay << std::endl;   
    }

    return 0;
}