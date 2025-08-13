#include "pch.h"
#include "CppUnitTest.h"
#include "Core/SystemScanner.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace NeuroCodTests {
    TEST_CLASS(SystemScannerTests) {
    public:
        TEST_METHOD(TestCPUDetection) {
            auto info = SystemScanner::GetCPUInfo();
            Assert::IsFalse(info.name.empty());
        }
        
        TEST_METHOD(StressTest) {
            bool result = SystemScanner::RunStressTest(5);
            Assert::IsTrue(result);
        }
    };
}