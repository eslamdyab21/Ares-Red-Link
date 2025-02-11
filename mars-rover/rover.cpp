#include <thread>
#include <mutex>

#include "rover.h"
#include "../logger/logger.h"

// Define shared resources
std::queue<DataPacket> sensorsDataQueue;
std::mutex queueMutex;
std::condition_variable queueCond;


// Function to read and queue sensor data
bool Rover::readSensorData(std::ifstream& file, std::string& line) {
    logMessage("INFO", "Rover::readSensorData -> Read line");

    return static_cast<bool>(std::getline(file, line));
}


void Rover::sendSensorData(std::string& line, double signal_delay) {
    logMessage("INFO", "Rover::sendSensorData -> Lock queue and push new data to the queue");

    auto sendTime = std::chrono::steady_clock::now() + std::chrono::seconds(static_cast<int>(signal_delay));

    {
        std::lock_guard<std::mutex> lock(queueMutex);
        sensorsDataQueue.push({line, sendTime});
    }

    logMessage("INFO", "Rover::sendSensorData -> Unlock queue and queueCond.notify_one");
}