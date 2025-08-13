#pragma once
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.System.Diagnostics.h>
#include <wrl.h>
#include <comdef.h>
#include <Wbemidl.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <string>
#include <map>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "dxgi.lib")
#pragma comment(lib, "d3d12.lib")

namespace NeuroCodHardware {
    class SystemScanner {
    public:
        static winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Data::Json::JsonObject> FullDiagnostic();
        static bool RunStressTest(int seconds);
        static winrt::Windows::Data::Json::JsonObject GetCachedResults();

    private:
        static winrt::Windows::Data::Json::JsonObject ScanCPU();
        static winrt::Windows::Data::Json::JsonObject ScanGPU();
        static winrt::Windows::Data::Json::JsonObject ScanRAM();
        static winrt::Windows::Data::Json::JsonObject ScanStorage();
        static winrt::Windows::Data::Json::JsonObject ScanNetwork();
        static winrt::Windows::Data::Json::JsonObject ScanOS();
        static bool CheckDirectX12Support();
        
        static inline winrt::Windows::Data::Json::JsonObject cachedResults;
    };
}