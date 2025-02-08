#ifndef EPHEMERIS_DATA_H
#define EPHEMERIS_DATA_H

#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct EphemerisEntry {
    std::string date;
    double distance_au;  
    double ra;           // Right Ascension
    double declination;  
};

class EphemerisData {
public:
    void loadSunEphemeris(const std::string& astro_object_ephemeris);
    void loadMarsEphemeris(const std::string& astro_object_ephemeris);
    const std::vector<EphemerisEntry>& getSunEphemerisData() const;
    const std::vector<EphemerisEntry>& getMarsEphemerisData() const;

private:
    std::vector<EphemerisEntry> sun_ephemeris_data;
    std::vector<EphemerisEntry> mars_ephemeris_data;
};

#endif // EPHEMERIS_DATA_H
