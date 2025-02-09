#ifndef COMMS_MANAGER_H
#define COMMS_MANAGER_H
#include <vector>

#include "../ephemeris/ephemeris_data.h"
#include "../mars-rover/rover.h"


class CommsManager {
public:
    double computeSignalDelay(const EphemerisEntry mars_ephemeris_entry, const EphemerisEntry sun_ephemeris_entry);
    void delayedTransmitter(const std::string& ip, int port);
    std::string getCurrentDate();
    
private:
    EphemerisData ephemeris;
    bool isSolarConjunction(const EphemerisEntry mars_ephemeris_entry, const EphemerisEntry sun_ephemeris_entry);
};

#endif // COMMS_MANAGER_H
