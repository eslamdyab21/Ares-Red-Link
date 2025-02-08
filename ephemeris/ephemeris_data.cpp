#include "ephemeris_data.h"
#include <fstream>

void EphemerisData::loadEphemeris(const std::string& astro_object_filename) {
    std::ifstream astro_object_file(astro_object_filename);
    std::string line;
    
    if (!astro_object_file.is_open()) {
        std::cerr << "Error: Unable to open ephemeris files." << std::endl;
        return;
    }
    
    // Skip header
    std::getline(astro_object_file, line);

    double ra_h, ra_m, ra_s;
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


        // Read Mars Declination and Distance (AU)
        std::getline(iss, temp, ','); entry.declination = std::stod(temp);
        std::getline(iss, temp, ','); entry.distance_au = std::stod(temp);


        // Store in vector
        astro_object_ephemeris.push_back(entry);
    }
}


const std::vector<EphemerisEntry>& EphemerisData::getEphemerisData() const {
    return astro_object_ephemeris;
}
