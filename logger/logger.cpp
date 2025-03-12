#include "logger.h"

void logMessage(const std::string level, const std::string message) {
    std::ofstream logFile("logfile.log", std::ios::app);
    
    // Get current time
    std::time_t now = std::time(nullptr);
    char timeStr[20];
    std::strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", std::localtime(&now));

    std::string logEntry = "[" + std::string(timeStr) + "] [" + level + "] " + message;
    
    
    
    // std::cout << logEntry << std::endl;
    
    // Write to log file
    if (logFile.is_open()) {
        logFile << logEntry << std::endl;
    }
}