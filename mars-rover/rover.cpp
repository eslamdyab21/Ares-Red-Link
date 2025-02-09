#include <thread>
#include <mutex>

#include "rover.h"


// Define shared resources
std::queue<DataPacket> sensorsDataQueue;
std::mutex queueMutex;
std::condition_variable queueCond;


// Function to read and queue sensor data
bool Rover::readSensorData(std::ifstream& file, std::string& line) {
    return static_cast<bool>(std::getline(file, line));
}


void Rover::sendSensorData(std::string& line, double signal_delay) {
    auto sendTime = std::chrono::steady_clock::now() + std::chrono::seconds(static_cast<int>(signal_delay));

    {
        std::lock_guard<std::mutex> lock(queueMutex);
        sensorsDataQueue.push({line, sendTime});
    }
}