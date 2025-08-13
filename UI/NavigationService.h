#pragma once
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Navigation.h>

class NavigationService {
public:
    static NavigationService& Get() {
        static NavigationService instance;
        return instance;
    }
    
    void Initialize(winrt::Windows::UI::Xaml::Controls::Frame frame) {
        m_frame = frame;
    }
    
    void NavigateTo(winrt::hstring const& pageTypeName) {
        m_frame.Navigate(winrt::xaml_typename<pageTypeName>());
    }

private:
    winrt::Windows::UI::Xaml::Controls::Frame m_frame{ nullptr };
};