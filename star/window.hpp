#pragma once
#ifndef UTILS_WINDOW_HPP
#define UTILS_WINDOW_HPP

#include <iostream>
#include <thread>
#include <windows.h>

namespace star {
    class console {
    public:
        template<typename T>
        static void log(T words) {
            std::cout << words;
        }

        static void wait_for_key_press() {
            std::cin.get();
        }

        bool create() {
            std::thread t([&] {
                bool ret = AllocConsole();
                if (ret) {
                    this->console_hwnd = GetConsoleWindow();
                }
            });
            t.join();
            return console_hwnd != nullptr;
        }

        ~console() {
            if (console_hwnd) {
                FreeConsole();
            }
        }

    private:
        HWND console_hwnd{};
    };
}

#endif //UTILS_WINDOW_HPP
