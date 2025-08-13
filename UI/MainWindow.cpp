#include "pch.h"
#include "MainWindow.h"
#include "App.xaml.h"
#include "MainPage.xaml.h"

using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Hosting;
using namespace Windows::UI::Xaml::Controls;

MainWindow::MainWindow(HINSTANCE hInstance) : hInstance(hInstance) {}

MainWindow::~MainWindow() {
    if (hWnd) DestroyWindow(hWnd);
}

bool MainWindow::Initialize() {
    WNDCLASS wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    RegisterClass(&wc);

    hWnd = CreateWindowEx(
        0,
        CLASS_NAME,
        L"NeuroCod v7.0+",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 1200, 800,
        nullptr, nullptr, hInstance, this
    );

    if (!hWnd) return false;

    CreateXAMLIslands();
    return true;
}

void MainWindow::Show() {
    ShowWindow(hWnd, SW_SHOW);
    UpdateWindow(hWnd);
}

void MainWindow::Close() {
    if (hWnd) DestroyWindow(hWnd);
}

LRESULT CALLBACK MainWindow::WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_CREATE) {
        CREATESTRUCT* pCreate = reinterpret_cast<CREATESTRUCT*>(lParam);
        SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pCreate->lpCreateParams));
        return 0;
    }
    
    MainWindow* pThis = reinterpret_cast<MainWindow*>(GetWindowLongPtr(hWnd, GWLP_USERDATA));
    
    if (pThis) {
        switch (message) {
        case WM_SIZE:
            pThis->ResizeXAMLIslands();
            return 0;
            
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        }
    }
    
    return DefWindowProc(hWnd, message, wParam, lParam);
}

void MainWindow::CreateXAMLIslands() {
    // Инициализация XAML Islands
    xamlSource = DesktopWindowXamlSource();
    
    auto interop = xamlSource.as<IDesktopWindowXamlSourceNative>();
    check_hresult(interop->AttachToWindow(hWnd));
    
    HWND islandHwnd;
    interop->get_WindowHandle(&islandHwnd);
    
    // Создание корневого фрейма
    rootFrame = Frame();
    xamlSource.Content(rootFrame);
    
    // Навигация на главную страницу
    rootFrame.Navigate(winrt::xaml_typename<NeuroCodUI::MainPage>());
    
    // Начальный размер
    ResizeXAMLIslands();
}

void MainWindow::ResizeXAMLIslands() {
    if (hWnd) {
        RECT rect;
        GetClientRect(hWnd, &rect);
        SetWindowPos(
            xamlSource.as<IDesktopWindowXamlSourceNative>()->get_WindowHandle(),
            nullptr, 
            0, 0, rect.right - rect.left, rect.bottom - rect.top,
            SWP_SHOWWINDOW
        );
    }
}