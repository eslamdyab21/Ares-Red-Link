#include "ephemeris_data.h"
#include <fstream>

void EphemerisData::loadSunEphemeris(const std::string& astro_object_filename) {
    std::ifstream astro_object_file(astro_object_filename);
    std::string line;
    
    if (!astro_object_file.is_open()) {
        std::cerr << "Error: Unable to open ephemeris files." << std::endl;
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
}


void EphemerisData::loadMarsEphemeris(const std::string& astro_object_filename) {
    std::ifstream astro_object_file(astro_object_filename);
    std::string line;
    
    if (!astro_object_file.is_open()) {
        std::cerr << "Error: Unable to open ephemeris files." << std::endl;
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
}


const std::vector<EphemerisEntry>& EphemerisData::getSunEphemerisData() const {
    return sun_ephemeris_data;
}


const std::vector<EphemerisEntry>& EphemerisData::getMarsEphemerisData() const {
    return mars_ephemeris_data;
}



EphemerisEntry EphemerisData::getSunEphemerisDataDate(const std::string& astro_object_filename, std::string date) {
    std::ifstream astro_object_file(astro_object_filename);
    std::string line;
    
    if (!astro_object_file.is_open()) {
        std::cerr << "Error: Unable to open ephemeris files." << std::endl;
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
            return entry;
        }
    }

    return EphemerisEntry();
}


EphemerisEntry EphemerisData::getMarsEphemerisDataDate(const std::string& astro_object_filename, std::string date) {
    std::ifstream astro_object_file(astro_object_filename);
    std::string line;
    
    if (!astro_object_file.is_open()) {
        std::cerr << "Error: Unable to open ephemeris files." << std::endl;
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
            return entry;
        }
    }

    return EphemerisEntry();
}