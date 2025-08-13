#pragma once
#include <string>
#include <fstream>
#include <mutex>

enum class LogLevel {
    Info,
    Warning,
    Error
};

class Logger {
public:
    static Logger& Get();
    void Log(LogLevel level, const std::string& message);
    
private:
    Logger();
    ~Logger();
    
    std::string LevelToString(LogLevel level);
    std::ofstream m_logFile;
    std::mutex m_mutex;
};