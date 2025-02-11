#include <fstream>

#include "ephemeris_data.h"
#include "../logger/logger.h"


void EphemerisData::loadSunEphemeris(const std::string& astro_object_filename) {
    logMessage("INFO", "EphemerisData::loadSunEphemeris-> Start");

    std::ifstream astro_object_file(astro_object_filename);
    std::string line;
    
    if (!astro_object_file.is_open()) {
        std::cerr << "Error: Unable to open ephemeris files." << std::endl;
        logMessage("ERROR", "Unable to open ephemeris files");
        return;
    }
    
    // Skip header
    std::getline(astro_object_file, line);

    double ra_h, ra_m, ra_s;
    double dec_d, dec_m, dec_s;
    while (std::getline(astro_object_file, line)) {
        std::istringstream iss(line);
        EphemerisEntry entry;
        std::string temp;

        // Read required columns
        std::getline(iss, entry.date, ',');

        // Skip JD (not needed)
        std::getline(iss, temp, ',');
        // Skip App GST (not needed)
        std::getline(iss, temp, ',');
        // Skip Equation of Time (not needed)
        std::getline(iss, temp, ',');


        // Read RA (h, m, s)
        std::getline(iss, temp, ' '); ra_h = std::stod(temp);
        std::getline(iss, temp, ' '); ra_m = std::stod(temp);
        std::getline(iss, temp, ','); ra_s = std::stod(temp);
        // Convert RA to decimal hours
        std::getline(iss, temp, ','); entry.ra = ra_h + (ra_m / 60.0) + (ra_s / 3600.0);


        // Read Apparent Declination (±DD:MM.M)
        std::getline(iss, temp, ' '); dec_d = std::stoi(temp);
        std::getline(iss, temp, ' '); dec_m = std::stoi(temp);
        std::getline(iss, temp, ','); dec_s = std::stod(temp);
        // Convert Declination to decimal degrees
        entry.declination = dec_d + (dec_m / 60.0) + (dec_s / 3600.0);


        // Read Declination and Distance (AU)
        std::getline(iss, temp, ','); entry.distance_au = std::stod(temp);


        // Store in vector
        sun_ephemeris_data.push_back(entry);
    }
    logMessage("INFO", "EphemerisData::loadSunEphemeris -> Done");
}


void EphemerisData::loadMarsEphemeris(const std::string& astro_object_filename) {
    logMessage("INFO", "EphemerisData::loadMarsEphemeris -> Start");

    std::ifstream astro_object_file(astro_object_filename);
    std::string line;
    
    if (!astro_object_file.is_open()) {
        std::cerr << "Error: Unable to open ephemeris files." << std::endl;
        logMessage("ERROR", "Unable to open ephemeris files");
        return;
    }
    
    // Skip header
    std::getline(astro_object_file, line);

    double ra_h, ra_m, ra_s;
    double dec_d, dec_m, dec_s;
    while (std::getline(astro_object_file, line)) {
        std::istringstream iss(line);
        EphemerisEntry entry;
        std::string temp;

        // Read required columns
        std::getline(iss, entry.date, ',');


        // Read RA (h, m, s)
        std::getline(iss, temp, ' '); ra_h = std::stod(temp);
        std::getline(iss, temp, ' '); ra_m = std::stod(temp);
        std::getline(iss, temp, ','); ra_s = std::stod(temp);
        // Convert RA to decimal hours
        std::getline(iss, temp, ','); entry.ra = ra_h + (ra_m / 60.0) + (ra_s / 3600.0);


        // Read Apparent Declination (±DD:MM.M)
        std::getline(iss, temp, ' '); dec_d = std::stoi(temp);
        std::getline(iss, temp, ' '); dec_m = std::stoi(temp);
        std::getline(iss, temp, ','); dec_s = std::stod(temp);
        // Convert Declination to decimal degrees
        entry.declination = dec_d + (dec_m / 60.0) + (dec_s / 3600.0);


        // Read Declination and Distance (AU)
        std::getline(iss, temp, ','); entry.distance_au = std::stod(temp);


        // Store in vector
        mars_ephemeris_data.push_back(entry);
    }
    logMessage("INFO", "EphemerisData::loadMarsEphemeris -> Done");
}


const std::vector<EphemerisEntry>& EphemerisData::getSunEphemerisData() const {
    logMessage("INFO", "EphemerisData::getSunEphemerisData -> Start");
    logMessage("INFO", "EphemerisData::getSunEphemerisData -> Done");

    return sun_ephemeris_data;
}


const std::vector<EphemerisEntry>& EphemerisData::getMarsEphemerisData() const {
    logMessage("INFO", "EphemerisData::getMarsEphemerisData -> Start");
    logMessage("INFO", "EphemerisData::getMarsEphemerisData -> Done");
    
    return mars_ephemeris_data;
}



EphemerisEntry EphemerisData::getSunEphemerisDataDate(const std::string& astro_object_filename, std::string date) {
    logMessage("INFO", "EphemerisData::getSunEphemerisDataDate -> Start");

    std::ifstream astro_object_file(astro_object_filename);
    std::string line;
    
    if (!astro_object_file.is_open()) {
        std::cerr << "Error: Unable to open ephemeris files." << std::endl;
        logMessage("ERROR", "Unable to open ephemeris files");
        return EphemerisEntry();
    }
    
    // Skip header
    std::getline(astro_object_file, line);

    double ra_h, ra_m, ra_s;
    double dec_d, dec_m, dec_s;
    while (std::getline(astro_object_file, line)) {
        std::istringstream iss(line);
        EphemerisEntry entry;
        std::string temp;

        // Read required columns
        std::getline(iss, entry.date, ',');

        // Skip JD (not needed)
        std::getline(iss, temp, ',');
        // Skip App GST (not needed)
        std::getline(iss, temp, ',');
        // Skip Equation of Time (not needed)
        std::getline(iss, temp, ',');


        // Read RA (h, m, s)
        std::getline(iss, temp, ' '); ra_h = std::stod(temp);
        std::getline(iss, temp, ' '); ra_m = std::stod(temp);
        std::getline(iss, temp, ','); ra_s = std::stod(temp);
        // Convert RA to decimal hours
        std::getline(iss, temp, ','); entry.ra = ra_h + (ra_m / 60.0) + (ra_s / 3600.0);


        // Read Apparent Declination (±DD:MM.M)
        std::getline(iss, temp, ' '); dec_d = std::stoi(temp);
        std::getline(iss, temp, ' '); dec_m = std::stoi(temp);
        std::getline(iss, temp, ','); dec_s = std::stod(temp);
        // Convert Declination to decimal degrees
        entry.declination = dec_d + (dec_m / 60.0) + (dec_s / 3600.0);


        // Read Declination and Distance (AU)
        std::getline(iss, temp, ','); entry.distance_au = std::stod(temp);


        
        if (entry.date == date) {
            logMessage("INFO", "EphemerisData::getSunEphemerisDataDate -> Found entry.date == date");
            logMessage("INFO", "EphemerisData::getSunEphemerisDataDate -> Done");
            return entry;
        }
    }

    logMessage("INFO", "EphemerisData::getSunEphemerisDataDate -> No match entry.date == date");
    logMessage("INFO", "EphemerisData::getSunEphemerisDataDate -> Done");
    return EphemerisEntry();
}


EphemerisEntry EphemerisData::getMarsEphemerisDataDate(const std::string& astro_object_filename, std::string date) {
    logMessage("INFO", "EphemerisData::getMarsEphemerisDataDate -> Start");

    std::ifstream astro_object_file(astro_object_filename);
    std::string line;
    
    if (!astro_object_file.is_open()) {
        std::cerr << "Error: Unable to open ephemeris files." << std::endl;
        logMessage("ERROR", "Unable to open ephemeris files");
        return EphemerisEntry();
    }
    
    // Skip header
    std::getline(astro_object_file, line);

    double ra_h, ra_m, ra_s;
    double dec_d, dec_m, dec_s;
    while (std::getline(astro_object_file, line)) {
        std::istringstream iss(line);
        EphemerisEntry entry;
        std::string temp;

        // Read required columns
        std::getline(iss, entry.date, ',');


        // Read RA (h, m, s)
        std::getline(iss, temp, ' '); ra_h = std::stod(temp);
        std::getline(iss, temp, ' '); ra_m = std::stod(temp);
        std::getline(iss, temp, ','); ra_s = std::stod(temp);
        // Convert RA to decimal hours
        std::getline(iss, temp, ','); entry.ra = ra_h + (ra_m / 60.0) + (ra_s / 3600.0);


        // Read Apparent Declination (±DD:MM.M)
        std::getline(iss, temp, ' '); dec_d = std::stoi(temp);
        std::getline(iss, temp, ' '); dec_m = std::stoi(temp);
        std::getline(iss, temp, ','); dec_s = std::stod(temp);
        // Convert Declination to decimal degrees
        entry.declination = dec_d + (dec_m / 60.0) + (dec_s / 3600.0);


        // Read Declination and Distance (AU)
        std::getline(iss, temp, ','); entry.distance_au = std::stod(temp);


        if (entry.date == date) {
            logMessage("INFO", "EphemerisData::getMarsEphemerisDataDate -> Found entry.date == date");
            logMessage("INFO", "EphemerisData::getMarsEphemerisDataDate -> Done");
            return entry;
        }
    }

    logMessage("INFO", "EphemerisData::getMarsEphemerisDataDate -> No match entry.date == date");
    logMessage("INFO", "EphemerisData::getMarsEphemerisDataDate -> Done");
    return EphemerisEntry();
}