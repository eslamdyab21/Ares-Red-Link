#ifndef ROVER_H
#define ROVER_H

#include <string>
#include <queue>
#include <fstream>
#include <iostream>
#include <condition_variable>




struct DataPacket {
    std::string data;
    std::chrono::steady_clock::time_point sendTime;
};

extern std::mutex queueMutex;
extern std::queue<DataPacket> sensorsDataQueue;
extern std::condition_variable queueCond;


class Rover {
public:
    bool readSensorData(std::ifstream& file, std::string& line);
    void sendSensorData(std::string& line, double signal_delay);

};

#endif // ROVER_H
