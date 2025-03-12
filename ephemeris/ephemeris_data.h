#ifndef EPHEMERIS_DATA_H
#define EPHEMERIS_DATA_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct EphemerisEntry {
    std::string date = "Jan 01";
    double distance_au = 0;  
    double ra = 0;           // Right Ascension
    double declination = 0;  
};

class EphemerisData {
public:
    void loadSunEphemeris(const std::string& astro_object_ephemeris);
    void loadMarsEphemeris(const std::string& astro_object_ephemeris);

    std::vector<EphemerisEntry>* getSunEphemerisData();
    std::vector<EphemerisEntry>* getMarsEphemerisData();

    EphemerisEntry getSunEphemerisDataDate(const std::string& astro_object_filename, std::string date);
    EphemerisEntry getMarsEphemerisDataDate(const std::string& astro_object_filename, std::string date);

    void clearEphemerisData();

private:
    std::vector<EphemerisEntry> sun_ephemeris_data;
    std::vector<EphemerisEntry> mars_ephemeris_data;
};

#endif // EPHEMERIS_DATA_H
