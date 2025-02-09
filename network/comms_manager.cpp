#include <cmath>
#include <array>
#include <chrono>
#include <cstring>
#include <arpa/inet.h>
#include <queue>
#include <unistd.h>

#include "comms_manager.h"



constexpr double DEG_TO_RAD = M_PI / 180.0;
constexpr double SOLAR_CONJUNCTION_ANGLE = 5.0; // Threshold in degrees
constexpr double SPEED_OF_LIGHT = 299792.458; // km/s
constexpr double AU_TO_KM = 149597870.7; // km

// Function to convert RA/Dec to 3D Cartesian coordinates (unit vector)
std::array<double, 3> toCartesian(double ra, double dec) {
    double ra_rad = ra * 15.0 * DEG_TO_RAD;  // Convert decimal hours to degrees, then to radians
    double dec_rad = dec * DEG_TO_RAD;       // Convert Dec to radians

    return {
        std::cos(ra_rad) * std::cos(dec_rad),  // x
        std::sin(ra_rad) * std::cos(dec_rad),  // y
        std::sin(dec_rad)                      // z
    };
}


// Check for conjunction
bool CommsManager::isSolarConjunction(const EphemerisEntry mars_ephemeris_entry, const EphemerisEntry sun_ephemeris_entry) {
    auto mars_vector = toCartesian(mars_ephemeris_entry.ra, mars_ephemeris_entry.declination);
    auto sun_vector = toCartesian(sun_ephemeris_entry.ra, sun_ephemeris_entry.declination);

    // Compute dot product
    double dot_product = mars_vector[0] * sun_vector[0] +
                         mars_vector[1] * sun_vector[1] +
                         mars_vector[2] * sun_vector[2];

    // Compute angle in degrees
    double angle_rad = std::acos(dot_product);  // Angle in radians
    double angle_deg = angle_rad * (180.0 / M_PI); // Convert to degrees

    return angle_deg < SOLAR_CONJUNCTION_ANGLE;
}



// Compute signal delay Earth-Mars, with conjunction check
double CommsManager::computeSignalDelay(const EphemerisEntry mars_ephemeris_entry, const EphemerisEntry sun_ephemeris_entry) {
    if (isSolarConjunction(mars_ephemeris_entry, sun_ephemeris_entry)) {
        std::cout << "WARNING: Solar conjunction on " << mars_ephemeris_entry.date << " - No communication possible!\n";
        return -1.0; // Signal blocked
    }

    double distance_km = mars_ephemeris_entry.distance_au * AU_TO_KM; // Convert AU to km
    return distance_km / SPEED_OF_LIGHT; // Light travel time in seconds
}



// UDP thread to send sensors data
void CommsManager::delayedTransmitter(const std::string& ip, int port) {
    int sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) {
        std::cerr << "Socket creation failed\n";
        return;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip.c_str(), &serverAddr.sin_addr);

    while (true) {
        std::unique_lock<std::mutex> lock(queueMutex);
        queueCond.wait(lock, [] { return !sensorsDataQueue.empty(); });

        if (!sensorsDataQueue.empty()) {
            DataPacket packet = sensorsDataQueue.front();
            auto now = std::chrono::steady_clock::now();

            if (now >= packet.sendTime) {
                sensorsDataQueue.pop();
                lock.unlock();

                sendto(sock, packet.data.c_str(), packet.data.size(), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
                lock.lock();
            } else {
                queueCond.wait_until(lock, packet.sendTime);
            }
        }
    }

    close(sock);
}



// Get the current time
std::string CommsManager::getCurrentDate() {
    std::time_t t = std::time(nullptr);
    std::tm* tm = std::localtime(&t);


    char buffer[10];
    std::strftime(buffer, sizeof(buffer), "%b %d", tm);


    return std::string(buffer);
}