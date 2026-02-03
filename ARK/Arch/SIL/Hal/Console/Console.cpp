#include "Console.hpp"
#include <iostream>
#include <cstdarg>
#include <cstdio>

namespace ARK {
    namespace HAL {
        namespace SIL {
            void Console::Initialize() {
            }

            void Console::Print(const char* format, ...) {
                va_list args;
                va_start(args, format);
                vprintf(format, args);
                va_end(args);
                printf("\n");
            }

            void Console::Success(const std::string& msg) {
                std::cout << "[SUCCESS] " << msg << std::endl;
            }

            void Console::Error(const std::string& msg) {
                std::cerr << "[ERROR] " << msg << std::endl;
            }
        }
    }
}
