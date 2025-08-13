#pragma once
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.System.Diagnostics.h>
#include <winrt/Windows.Data.Json.h>
#include <memory>
#include <atomic>
#include <thread>

namespace NeuroCodMonitor {
    class ResourceMonitor {
    public:
        ResourceMonitor();
        ~ResourceMonitor();

        void Start();
        void Stop();
        winrt::Windows::Data::Json::JsonObject GetCurrentMetrics();

    private:
        void MonitoringThread();
        winrt::Windows::Data::Json::JsonObject CollectMetrics();

        std::atomic<bool> isRunning{false};
        std::unique_ptr<std::thread> monitorThread;
        winrt::Windows::Data::Json::JsonObject currentMetrics;
    };
}