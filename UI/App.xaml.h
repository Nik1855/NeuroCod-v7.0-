#pragma once
#include "App.g.h"

namespace winrt::NeuroCodUI::implementation {
    struct App : AppT<App> {
        App();
        void OnLaunched(winrt::Microsoft::UI::Xaml::LaunchActivatedEventArgs const& args);
        
    private:
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
    };
}