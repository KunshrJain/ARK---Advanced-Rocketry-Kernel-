#include "Uart.hpp"
#include <iostream>
#include <cstdio>

namespace ARK {
    namespace HAL {
        namespace SIL {
            void UART::Init(uint8_t port_num, uint8_t tx_pin, uint8_t rx_pin, uint32_t baudrate) {
                // std::cout << "[SIL] UART Init Port " << (int)port_num << std::endl;
            }

            void UART::Write(const uint8_t* data, size_t len) {
                // std::cout.write(reinterpret_cast<const char*>(data), len);
            }

            void UART::Write(char c) {
                // std::cout << c;
            }

            void UART::Write(const char* str) {
                // std::cout << str;
            }

            size_t UART::Read(uint8_t* buffer, size_t len, uint32_t timeout_ms) {
                return 0; // Simulate no data
            }
        }
    }
}
