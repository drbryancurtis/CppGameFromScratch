#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>

enum class LogLevel {
    INFO,
    WARNING,
    ERR // 'ERR' to avoid conflicts with 'ERROR' macros in Windows.h
};

class Logger {
public:
    // Initializes the log file
    static void Init(const std::string& filename);

    // The main logging function
    static void Log(LogLevel level, const std::string& message);

    // Helper for SDL-specific errors
    static void LogSDLError(const std::string& context);

    static void Shutdown();

private:
    static std::ofstream m_FileStream;
    static std::string GetTimestamp();
};