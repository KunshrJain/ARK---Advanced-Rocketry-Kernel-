#pragma once
#include "ARK/HAL/Uart/Uart.hpp"
#include "driver/uart.h"
#include <cstring>

namespace ARK {
    namespace HAL {
        namespace Esp32 {
            class UART : public ARK::HAL::UART {
            public:
                void Init(uint8_t port_num, uint8_t tx_pin, uint8_t rx_pin, uint32_t baudrate) override {
                    _port = (port_num == 0) ? UART_NUM_0 : (port_num == 1 ? UART_NUM_1 : UART_NUM_2);
                    
                    uart_config_t uart_config = {};
                    uart_config.baud_rate = (int)baudrate;
                    uart_config.data_bits = UART_DATA_8_BITS;
                    uart_config.parity    = UART_PARITY_DISABLE;
                    uart_config.stop_bits = UART_STOP_BITS_1;
                    uart_config.flow_ctrl = UART_HW_FLOWCTRL_DISABLE;
                    uart_config.rx_flow_ctrl_thresh = 122; // Default
                    uart_config.source_clk = UART_SCLK_DEFAULT;
                    uart_driver_install(_port, 1024 * 2, 0, 0, NULL, 0);
                    uart_param_config(_port, &uart_config);
                    uart_set_pin(_port, tx_pin, rx_pin, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
                }

                void Write(const uint8_t* data, size_t len) override {
                    uart_write_bytes(_port, (const char*)data, len);
                }

                void Write(char c) override {
                    uart_write_bytes(_port, &c, 1);
                }

                void Write(const char* str) override {
                    uart_write_bytes(_port, str, strlen(str));
                }

                size_t Read(uint8_t* buffer, size_t len, uint32_t timeout_ms) override {
                     return uart_read_bytes(_port, buffer, len, timeout_ms / portTICK_PERIOD_MS);
                }

            private:
                uart_port_t _port;
            };
        }
    }
}
