#include "Logger.h"
#include <ctime>
#include <iomanip>

Logger& Logger::getInstance() {
    static Logger instance;
    return instance;
}

void Logger::log(LogLevel level, const std::string& message) {    
    if (!logStream.is_open()) {
        openLogFile();
    }
    
    if (logStream.is_open()) {
        std::time_t now = std::time(nullptr);
        logStream << "[" << std::put_time(std::localtime(&now), "%Y-%m-%d %H:%M:%S") << "] "
                  << getLogLevelString(level) << ": " << message << std::endl;
    } else {
        std::cerr << "Unable to write to log file: " << logFile << std::endl;
    }
}

void Logger::setLogFile(const std::string& filename) {
    logFile = filename;
    if (logStream.is_open()) {
        logStream.close();
    }
    openLogFile();
}

Logger::~Logger() {
    if (logStream.is_open()) {
        logStream.close();
    }
}

void Logger::openLogFile() {
    logStream.open(logFile, std::ios_base::app);
    if (!logStream.is_open()) {
        std::cerr << "Failed to open log file: " << logFile << std::endl;
    }
}

std::string Logger::getLogLevelString(LogLevel level) {
    switch (level) {
        case INFO:
            return "INFO";
        case WARNING:
            return "WARNING";
        case ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

Logger& logger = Logger::getInstance();

