#pragma once
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <Windows.h>

class MainWindow {
public:
    MainWindow(HINSTANCE hInstance);
    ~MainWindow();
    
    bool Initialize();
    void Show();
    void Close();

private:
    static LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
    void CreateXAMLIslands();
    void ResizeXAMLIslands();
    
    HINSTANCE hInstance;
    HWND hWnd = nullptr;
    winrt::Windows::UI::Xaml::Hosting::DesktopWindowXamlSource xamlSource;
    winrt::Windows::UI::Xaml::Controls::Frame rootFrame{nullptr};
    const wchar_t* CLASS_NAME = L"NeuroCodMainWindow";
};