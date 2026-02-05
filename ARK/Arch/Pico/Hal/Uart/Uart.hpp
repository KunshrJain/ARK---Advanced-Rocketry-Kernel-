#pragma once
#include "ARK/HAL/Uart/Uart.hpp"
#include "pico/stdlib.h"
#include "hardware/uart.h"

namespace ARK {
    namespace HAL {
        namespace Pico {
            class UART : public ARK::HAL::UART {
            public:
                void Init(uint8_t port_num, uint8_t tx_pin, uint8_t rx_pin, uint32_t baudrate) override {
                    _inst = (port_num == 0) ? uart0 : uart1;
                    uart_init(_inst, baudrate);
                    gpio_set_function(tx_pin, GPIO_FUNC_UART);
                    gpio_set_function(rx_pin, GPIO_FUNC_UART);
                }

                void Write(const uint8_t* data, size_t len) override {
                    uart_write_blocking(_inst, data, len);
                }

                void Write(char c) override {
                    uart_putc(_inst, c);
                }

                void Write(const char* str) override {
                    uart_puts(_inst, str);
                }

                size_t Read(uint8_t* buffer, size_t len, uint32_t timeout_ms) override {
                    size_t read = 0;
                    absolute_time_t target = make_timeout_time_ms(timeout_ms);
                    
                    while (read < len) {
                         if (uart_is_readable(_inst)) {
                             buffer[read++] = uart_getc(_inst);
                         } else if (timeout_ms > 0 && time_reached(target)) {
                             break;
                         }
                    }
                    return read;
                }

            private:
                uart_inst_t* _inst = nullptr;
            };
        }
    }
}
