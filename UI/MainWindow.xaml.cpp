#include "pch.h"
#include "MainWindow.xaml.h"
#include "MainPage.xaml.h"
#include "NavigationService.h"

namespace winrt::NeuroCodUI::implementation {
    MainWindow::MainWindow() {
        InitializeComponent();
        NavigationService::Get().Initialize(MainFrame());
        NavigationService::Get().NavigateTo(xaml_typename<NeuroCodUI::MainPage>());
    }
}