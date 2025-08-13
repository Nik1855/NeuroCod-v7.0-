#include "pch.h"
#include "Settings.h"
#include <fstream>
#include <winrt/Windows.Storage.h>

void Settings::Load() {
    try {
        auto localFolder = winrt::Windows::Storage::ApplicationData::Current().LocalFolder();
        auto file = localFolder.GetFileAsync(L"settings.json").get();
        auto content = winrt::Windows::Storage::FileIO::ReadTextAsync(file).get();
        
        json = nlohmann::json::parse(content);
        language = json["language"].get<std::string>();
        theme = json["theme"].get<std::string>();
    } catch (...) {
        // Дефолтные настройки
        language = "en-US";
        theme = "dark";
    }
}

void Settings::Save() {
    json["language"] = language;
    json["theme"] = theme;

    auto localFolder = winrt::Windows::Storage::ApplicationData::Current().LocalFolder();
    auto file = localFolder.CreateFileAsync(L"settings.json", 
        winrt::Windows::Storage::CreationCollisionOption::ReplaceExisting).get();
    
    winrt::Windows::Storage::FileIO::WriteTextAsync(file, 
        winrt::to_hstring(json.dump()));
}