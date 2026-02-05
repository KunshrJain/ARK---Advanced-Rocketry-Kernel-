#pragma once
#include <cstdint>
#include <cstddef>

namespace ARK {
    namespace HAL {
        class UART {
        public:
            virtual ~UART() = default;

            // Initialize the UART
            virtual void Init(uint8_t port_num, uint8_t tx_pin, uint8_t rx_pin, uint32_t baudrate) = 0;

            virtual void Write(const uint8_t* data, size_t len) = 0;
            virtual void Write(char c) = 0;
            virtual void Write(const char* str) = 0;
            
            // Read with timeout
            // Returns bytes read
            virtual size_t Read(uint8_t* buffer, size_t len, uint32_t timeout_ms = 0) = 0;
        };
    }
}
