#include "Console.hpp"
#include "pico/stdlib.h"
#include <cstdio>

namespace ARK {
    namespace HAL {
        namespace Pico {
            void Console::Initialize() {
                stdio_init_all();
            }

            void Console::Print(const char* format, ...) {
                va_list args;
                va_start(args, format);
                vprintf(format, args);
                va_end(args);
                printf("\n");
            }

            void Console::Success(const std::string& msg) {
                printf("[SUCCESS] %s\n", msg.c_str());
            }

            void Console::Error(const std::string& msg) {
                printf("[ERROR] %s\n", msg.c_str());
            }
        }
    }
}
