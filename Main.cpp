#include "pch.h"
#include "Main.h"
#include "App.xaml.h"

using namespace winrt;
using namespace Microsoft::UI::Xaml;

namespace winrt::NeuroCod::implementation {
    int Main::wWinMain() noexcept {
        init_apartment(apartment_type::single_threaded);
        
        Application::Start([](auto&&) {
            make<NeuroCod::implementation::App>();
        });
        
        return 0;
    }
}