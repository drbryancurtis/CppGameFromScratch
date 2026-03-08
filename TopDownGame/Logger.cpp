#include "Logger.hpp"
#include <SDL3/SDL.h>

std::ofstream Logger::m_FileStream;

void Logger::Init(const std::string& filename) {
    m_FileStream.open(filename, std::ios::out | std::ios::trunc);
    if (m_FileStream.is_open()) {
        Log(LogLevel::INFO, "Logger initialized. File: " + filename);
    }
}

std::string Logger::GetTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto in_time_t = std::chrono::system_clock::to_time_t(now);

    struct tm buf;
    // localtime_s returns 0 on success in MSVC
    localtime_s(&buf, &in_time_t);

    std::stringstream ss;
    // Just pass &buf directly to put_time
    ss << std::put_time(&buf, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void Logger::Log(LogLevel level, const std::string& message) {
    std::string levelStr;
    switch (level) {
    case LogLevel::INFO:    levelStr = "[INFO]";    break;
    case LogLevel::WARNING: levelStr = "[WARNING]"; break;
    case LogLevel::ERR:     levelStr = "[ERROR]";   break;
    }

    std::string output = GetTimestamp() + " " + levelStr + " " + message;

    // Output to Console for the developer
    std::cout << output << std::endl;

    // Output to File for the record
    if (m_FileStream.is_open()) {
        m_FileStream << output << std::endl;
        m_FileStream.flush(); // Ensure it writes even if the game crashes immediately after
    }
}

void Logger::LogSDLError(const std::string& context) {
    std::string fullMsg = context + " | SDL_Error: " + SDL_GetError();
    Log(LogLevel::ERR, fullMsg);
}

void Logger::Shutdown() {
    if (m_FileStream.is_open()) {
        Log(LogLevel::INFO, "Logger shutting down.");
        m_FileStream.close();
    }
}