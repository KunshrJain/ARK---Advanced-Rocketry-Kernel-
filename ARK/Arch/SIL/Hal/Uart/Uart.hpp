#pragma once
#include "ARK/HAL/Uart/Uart.hpp"

namespace ARK {
    namespace HAL {
        namespace SIL {
            class UART : public ARK::HAL::UART {
            public:
                void Init(uint8_t port_num, uint8_t tx_pin, uint8_t rx_pin, uint32_t baudrate) override;
                void Write(const uint8_t* data, size_t len) override;
                void Write(char c) override;
                void Write(const char* str) override;
                size_t Read(uint8_t* buffer, size_t len, uint32_t timeout_ms = 0) override;
            };
        }
    }
}
