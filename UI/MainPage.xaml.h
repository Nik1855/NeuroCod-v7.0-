#pragma once
#include "MainPage.g.h"

namespace winrt::NeuroCodUI::implementation {
    struct MainPage : MainPageT<MainPage> {
        MainPage();
        
        void OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        void StartScan_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        
    private:
        void UpdateLocalization();
        void ApplyTheme();
    };
}