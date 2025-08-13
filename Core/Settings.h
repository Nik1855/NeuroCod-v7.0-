#pragma once
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Data.Json.h>
#include <mutex>

namespace NeuroCodConfig {
    class Settings {
    public:
        static Settings& GetInstance();
        
        void Load();
        void Save();
        
        winrt::hstring GetLanguage();
        void SetLanguage(const winrt::hstring& language);
        
        bool IsDarkTheme();
        void SetDarkTheme(bool enabled);
        
        // Другие настройки...

    private:
        Settings();
        winrt::Windows::Storage::ApplicationDataContainer localSettings{
            winrt::Windows::Storage::ApplicationData::Current().LocalSettings()};
        
        winrt::hstring currentLanguage{L"en-US"};
        bool darkTheme{true};
        std::mutex settingsMutex;
    };
}