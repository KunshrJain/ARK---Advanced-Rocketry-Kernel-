#pragma once
#include <string>
#include <cstdarg>

namespace ARK {
    namespace HAL {
        class Console {
        public:
            virtual ~Console() = default;
            virtual void Initialize() = 0;
            virtual void Print(const char* format, ...) = 0;
            virtual void Success(const std::string& msg) = 0;
            virtual void Error(const std::string& msg) = 0;
        };
    }
    extern HAL::Console& SystemConsole;
}
