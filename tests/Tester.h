#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <functional>

class Tester {
public:
    static void addTest(const std::string& name, const std::function<void()>& testFunc) {
        getTests().emplace_back(name, testFunc);
    }

    static void runTests() {
        int passed = 0;
        int failed = 0;

        for (const auto& test : getTests()) {
            try {
                test.second(); // Run the test
                std::cout << "[PASS] " << test.first << std::endl;
                passed++;
            } catch (const std::exception& e) {
                std::cout << "[FAIL] " << test.first << ": " << e.what() << std::endl;
                failed++;
            }
        }

        std::cout << "\nSummary:\n"
                  << "  Passed: " << passed << "\n"
                  << "  Failed: " << failed << "\n"
                  << "  Total: " << passed + failed << "\n";
    }

    static void assertTrue(bool condition, const std::string& message = "") {
        if (!condition) throw std::runtime_error(message.empty() ? "Not true" : message);
    }

    template<class T>
    static void assertEqual(T expected, T actual, const std::string& message = "") {
 
        if (expected != actual) {
            if constexpr (std::is_same_v<T, std::string>) {
                throw std::runtime_error(message.empty() ? 
                    "Expected " + expected  + ", got " + actual : message);
            }
            else {
                throw std::runtime_error(message.empty() ? 
                    "Expected " + std::to_string(expected) + ", got " + std::to_string(actual) : message);
            } 
        }
            
    }

private:
    static std::vector<std::pair<std::string, std::function<void()>>>& getTests() {
        static std::vector<std::pair<std::string, std::function<void()>>> tests;
        return tests;
    }
};

#define TEST(name) \
    static void name(); \
    static struct name##_Registration { \
        name##_Registration() { Tester::addTest(#name, name); } \
    } name##_registration; \
    static void name()
