#pragma once

// Стандартные заголовки
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.System.Diagnostics.h>
#include <winrt/Windows.UI.Xaml.Controls.h>
#include <winrt/Windows.UI.Xaml.Navigation.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.XamlTypeInfo.h>  // Добавлено для поддержки XAML

#include <string>
#include <thread>
#include <fstream>
#include <nlohmann/json.hpp>
#include <coroutine>  // Используем стандартные корутины C++20
#include <random>     // Для заглушки GPU в ResourceMonitor

// Для работы с корутинами в C++20
namespace winrt {
    template <typename... Args>
    struct await_adapter<Windows::Foundation::IAsyncAction> {
        Windows::Foundation::IAsyncAction const& async;
        bool await_ready() const { return async.Status() == Windows::Foundation::AsyncStatus::Completed; }
        void await_suspend(std::experimental::coroutine_handle<> handle) const {
            async.Completed([handle](auto const&, auto const&) { handle(); });
        }
        void await_resume() const { async.GetResults(); }
    };
}