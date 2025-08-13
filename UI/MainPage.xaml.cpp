#include "pch.h"
#include "MainPage.xaml.h"
#include "Core/SystemScanner.h"
#include "Core/Settings.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::NeuroCodUI::implementation {
    MainPage::MainPage() {
        InitializeComponent();
        Settings::Instance().Load();
        UpdateLocalization();
        ApplyTheme();
    }

    void MainPage::UpdateLocalization() {
        ResourceLoader loader;
        WelcomeText().Text(loader.GetString(L"Welcome_Title"));
        ScanButton().Content(box_value(loader.GetString(L"Buttons_StartScan")));
    }

    void MainPage::ApplyTheme() {
        if (Settings::Instance().theme == "dark") {
            RequestedTheme(ElementTheme::Dark);
        } else {
            RequestedTheme(ElementTheme::Light);
        }
    }

    fire_and_forget MainPage::StartScan_Click(IInspectable const&, RoutedEventArgs const&) {
        co_await SystemScanner::FullDiagnosticAsync();
    }
}