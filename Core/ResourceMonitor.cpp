#include "pch.h"
#include "ResourceMonitor.h"
#include <winrt/Windows.System.Diagnostics.h>
#include <random>  // Добавлено для генерации случайных чисел

using namespace winrt;
using namespace Windows::System::Diagnostics;

// ... остальной код ...

float ResourceMonitor::GetGpuUsage() {
    // Временная заглушка для Windows 10
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(5.0f, 25.0f);
    return dis(gen);
}
  
float ResourceMonitor::GetGpuUsage() {
    // Реальная реализация требует DXGI
    // Заглушка для Windows 10
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_real_distribution<float> dis(5.0f, 25.0f);
    return dis(gen);
}

void ResourceMonitor::StopMonitoring() {
    m_monitoring = false;
    if (m_monitorThread.joinable()) {
        m_monitorThread.join();
    }
}