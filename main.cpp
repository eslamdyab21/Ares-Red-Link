#include <iostream>
#include <vector>
#include <array>
#include <fstream>
#include <thread>


#include "ephemeris/ephemeris_data.h"
#include "network/comms_manager.h"



void saveCSV(std::ofstream* outputFile, std::string udp_packet) {

    if (outputFile->is_open()) 
        *outputFile << udp_packet << '\n';
    
}



void udpThread(CommsManager *CommsManager, const std::string& ip, int port) {
    CommsManager->UDPTransmitter(ip, port);
}



int main() {
    EphemerisData EphemerisData;
    CommsManager CommsManager;

    // UDPThread
    std::thread transmitterThread(udpThread, &CommsManager, "127.0.0.1", 12345);


    // Write output file headers
    std::ofstream outputFile("link_data.csv");
    if (outputFile.is_open()) {
        outputFile  << "Date" << ";" << "RA" << ";" << "Dec" << ";" <<"Mars Coordinates"
                    << ";" << "Sun Coordinates" << ";" << "Distance" 
                    << ";" << "Angle" << ";" << "Signal Delay" << std::endl;                       
    }
    

    std::string mars_ephemeris_file, sun_ephemeris_file;
    std::string years[] = {"2020", "2021", "2022", "2023", "2024", "2025",
                           "2026", "2027", "2028", "2029", "2030"};

    std::array<double, 3> mars_coordinates, sun_coordinates;
    double signal_delay, mars_sun_angle;
    std::ostringstream udp_packet;


    // Compute signal delay, coordinates & angle for each record for each year
    for (int i = 0; i < sizeof(years) / sizeof(years[0]); i++) {
        mars_ephemeris_file = std::string("source-data/mars") + years[i] + ".csv";
        sun_ephemeris_file  = std::string("source-data/sun") + years[i] + ".csv";

        EphemerisData.loadMarsEphemeris(mars_ephemeris_file);
        std::vector<EphemerisEntry>* mars_ephemeris_data = EphemerisData.getMarsEphemerisData();

        EphemerisData.loadSunEphemeris(sun_ephemeris_file);
        std::vector<EphemerisEntry>* sun_ephemeris_data = EphemerisData.getSunEphemerisData();


        for (int j = 0; j < mars_ephemeris_data->size(); j++) {
            mars_coordinates = CommsManager.toCartesian((*mars_ephemeris_data)[j].ra, (*mars_ephemeris_data)[j].declination);
            sun_coordinates  = CommsManager.toCartesian((*sun_ephemeris_data)[j].ra, (*sun_ephemeris_data)[j].declination);
            
            mars_sun_angle = CommsManager.computeMarsSunAngle((*mars_ephemeris_data)[j], (*sun_ephemeris_data)[j]);
            signal_delay = CommsManager.computeSignalDelay((*mars_ephemeris_data)[j], (*sun_ephemeris_data)[j]);

            
            
            // Single CSV-formatted string for UDP thread
            udp_packet.str("");
            udp_packet << (*mars_ephemeris_data)[j].date << ", " << years[i] << ";"
                    << (*mars_ephemeris_data)[j].ra << ";"
                    << (*mars_ephemeris_data)[j].declination << ";"
                    << mars_coordinates[0] << "," << mars_coordinates[1] << "," << mars_coordinates[2] << ";"
                    << sun_coordinates[0] << "," << sun_coordinates[1] << "," << sun_coordinates[2] << ";"
                    << (*mars_ephemeris_data)[j].distance_au << ";"
                    << mars_sun_angle << ";"
                    << signal_delay;
                    
            CommsManager.addToQueue(udp_packet.str());
            saveCSV(&outputFile, udp_packet.str());


            std::cout << "Date: " << (*mars_ephemeris_data)[j].date << ", " << years[i]
                    << "; RA: " << (*mars_ephemeris_data)[j].ra
                    << "; Dec: " << (*mars_ephemeris_data)[j].declination
                    << "; Mars Coordinates: " << mars_coordinates[0] << "," << mars_coordinates[1] << "," << mars_coordinates[2]
                    << "; Sun Coordinates: " << sun_coordinates[0] << "," << sun_coordinates[1] << "," << sun_coordinates[2]
                    << "; Distance (AU): " << (*mars_ephemeris_data)[j].distance_au   
                    << "; Angle: " << mars_sun_angle  
                    << "; Signal Delay: " << signal_delay << std::endl;   
        }

        EphemerisData.clearEphemerisData();
    }


    outputFile.close();
    CommsManager.stopUDPThread();
    transmitterThread.join();

    return 0;
}