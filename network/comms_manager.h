#ifndef COMMS_MANAGER_H
#define COMMS_MANAGER_H
#include <vector>

#include "../ephemeris/ephemeris_data.h"


class CommsManager {
public:
    double computeSignalDelay(const EphemerisEntry mars_ephemeris_entry, const EphemerisEntry sun_ephemeris_entry);
    bool isSolarConjunction(const EphemerisEntry mars_ephemeris_entry, const EphemerisEntry sun_ephemeris_entry);

private:
    EphemerisData ephemeris;
};

#endif // COMMS_MANAGER_H
