#include "pch.h"
#include "SystemScanner.h"
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.System.Threading.h>
#include <iostream>
#include <fstream>
#include <comutil.h>

using namespace winrt;
using namespace Windows::Data::Json;
using namespace Windows::Foundation;
using namespace Windows::System::Threading;
using namespace Microsoft::WRL;

namespace NeuroCodHardware {

    IAsyncOperation<JsonObject> SystemScanner::FullDiagnostic() {
        co_await resume_background();

        JsonObject result;
        result.Insert(L"cpu", ScanCPU());
        result.Insert(L"gpu", ScanGPU());
        result.Insert(L"ram", ScanRAM());
        result.Insert(L"storage", ScanStorage());
        result.Insert(L"network", ScanNetwork());
        result.Insert(L"os", ScanOS());
        result.Insert(L"dx12_support", JsonValue::CreateBooleanValue(CheckDirectX12Support()));

        cachedResults = result;
        co_return result;
    }

    JsonObject SystemScanner::ScanCPU() {
        JsonObject cpuInfo;
        HRESULT hr = CoInitializeEx(0, COINIT_MULTITHREADED);
        if (FAILED(hr)) return cpuInfo;

        IWbemLocator* pLoc = nullptr;
        hr = CoCreateInstance(CLSID_WbemLocator, 0, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&pLoc);
        if (FAILED(hr)) return cpuInfo;

        IWbemServices* pSvc = nullptr;
        hr = pLoc->ConnectServer(_bstr_t(L"ROOT\\CIMV2"), nullptr, nullptr, 0, nullptr, 0, 0, &pSvc);
        if (FAILED(hr)) return cpuInfo;

        hr = CoSetProxyBlanket(pSvc, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, nullptr, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE);
        if (FAILED(hr)) return cpuInfo;

        IEnumWbemClassObject* pEnumerator = nullptr;
        hr = pSvc->ExecQuery(bstr_t("WQL"), bstr_t("SELECT * FROM Win32_Processor"), WBEM_FLAG_FORWARD_ONLY, nullptr, &pEnumerator);
        if (FAILED(hr)) return cpuInfo;

        IWbemClassObject* pclsObj = nullptr;
        ULONG uReturn = 0;
        while (pEnumerator) {
            hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
            if (uReturn == 0) break;

            VARIANT vtProp;
            hr = pclsObj->Get(L"Name", 0, &vtProp, 0, 0);
            if (SUCCEEDED(hr)) cpuInfo.Insert(L"name", JsonValue::CreateStringValue(vtProp.bstrVal));
            VariantClear(&vtProp);

            // Добавьте другие параметры (ядра, потоки, частота и т.д.)
            pclsObj->Release();
        }

        pSvc->Release();
        pLoc->Release();
        CoUninitialize();
        return cpuInfo;
    }

    // Аналогичные реализации для ScanGPU(), ScanRAM() и других методов
    // ...

    bool SystemScanner::CheckDirectX12Support() {
        HMODULE hD3D12 = LoadLibrary(L"d3d12.dll");
        if (!hD3D12) return false;
        FreeLibrary(hD3D12);
        return true;
    }

    bool SystemScanner::RunStressTest(int seconds) {
        // Реализация стресс-теста
        return true;
    }

    JsonObject SystemScanner::GetCachedResults() {
        return cachedResults;
    }
}