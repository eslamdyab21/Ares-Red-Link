#ifndef COMMS_MANAGER_H
#define COMMS_MANAGER_H
#include <vector>

#include "../ephemeris/ephemeris_data.h"
#include "../mars-rover/rover.h"


class CommsManager {
public:
    double computeSignalDelay(EphemerisEntry mars_ephemeris_entry, EphemerisEntry sun_ephemeris_entry);
    void delayedTransmitter(const std::string& ip, int port);

    std::array<double, 3> toCartesian(double ra, double dec);
    double computeMarsSunAngle(EphemerisEntry mars_ephemeris_entry, EphemerisEntry sun_ephemeris_entry);
    
    void UDPTransmitter(const std::string& ip, int port);
    void addToQueue(const std::string& data);
    void stopUDPThread();

    std::string getCurrentDate();
    
    
private:
    EphemerisData ephemeris;
    bool isSolarConjunction(EphemerisEntry mars_ephemeris_entry, EphemerisEntry sun_ephemeris_entry);

    std::mutex queueMutexUDP;
    std::queue<std::string> queueUDP;
    std::condition_variable queueCondUDP;
    bool runningUDPThread = true;
};

#endif // COMMS_MANAGER_H
