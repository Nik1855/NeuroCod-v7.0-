#include "pch.h"
#include "Logger.h"
#include <ctime>
#include <iomanip>

Logger& Logger::Get() {
    static Logger instance;
    return instance;
}

void Logger::Log(LogLevel level, const std::string& message) {
    std::time_t t = std::time(nullptr);
    std::tm tm;
    localtime_s(&tm, &t);
    
    std::ostringstream ss;
    ss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S") << " ["
       << LevelToString(level) << "] " << message;
    
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_logFile.is_open()) {
        m_logFile << ss.str() << std::endl;
    }
}

Logger::Logger() {
    auto path = winrt::Windows::Storage::ApplicationData::Current().LocalFolder().Path();
    m_logFile.open(path + L"\\neurocod.log", std::ios::app);
}