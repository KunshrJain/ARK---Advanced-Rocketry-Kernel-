#pragma once
#include "ARK/HAL/Console/Console.hpp"

namespace ARK {
    namespace HAL {
        namespace Pico {
            class Console final : public HAL::Console {
            public:
                void Initialize() override;
                void Print(const char* format, ...) override;
                void Success(const std::string& msg) override;
                void Error(const std::string& msg) override;
            };
        }
    }
}
