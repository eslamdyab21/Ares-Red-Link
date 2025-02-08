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
    void loadEphemeris(const std::string& astro_object_ephemeris);
    const std::vector<EphemerisEntry>& getEphemerisData() const;

private:
    std::vector<EphemerisEntry> astro_object_ephemeris;
};

#endif // EPHEMERIS_DATA_H
