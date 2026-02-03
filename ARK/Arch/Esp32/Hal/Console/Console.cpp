#include "Console.hpp"
#include <cstdio>
#include <cstdarg>

namespace ARK {
    namespace HAL {
        namespace Esp32 {
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
                printf("[SUCCESS] %s\n", msg.c_str());
            }

            void Console::Error(const std::string& msg) {
                printf("[ERROR] %s\n", msg.c_str());
            }
        }
    }
}
