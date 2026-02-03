#include "Uart.hpp"
#include "ARK/HAL/Console/Console.hpp"

#ifdef ARK_ARCH_PICO
    #include "hardware/uart.h"
    #include "pico/stdlib.h"

    void ARK::UART::Setup(uint32_t baudrate) {
        uart_init(uart_default, baudrate);
        gpio_set_function(PICO_DEFAULT_UART_TX_PIN, GPIO_FUNC_UART);
        gpio_set_function(PICO_DEFAULT_UART_RX_PIN, GPIO_FUNC_UART);
    }

    void ARK::UART::SendString(const std::string& data) {
        uart_puts(uart_default, data.c_str());
    }

    bool ARK::UART::DataAvailable() {
        return uart_is_readable(uart_default);
    }

    uint8_t ARK::UART::ReceiveByte() {
        return uart_getc(uart_default);
    }
#elif defined(ARK_ARCH_ESP32)
    #include "driver/uart.h"
    #include "driver/gpio.h"

    #define UART_NUM UART_NUM_1
    #define UART_TX_PIN GPIO_NUM_17
    #define UART_RX_PIN GPIO_NUM_16
    #define BUF_SIZE (1024)

    void ARK::UART::Setup(uint32_t baudrate) {
        uart_config_t uart_config = {
            .baud_rate = (int)baudrate,
            .data_bits = UART_DATA_8_BITS,
            .parity    = UART_PARITY_DISABLE,
            .stop_bits = UART_STOP_BITS_1,
            .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
            .source_clk = UART_SCLK_APB,
        };
        uart_driver_install(UART_NUM, BUF_SIZE * 2, 0, 0, NULL, 0);
        uart_param_config(UART_NUM, &uart_config);
        uart_set_pin(UART_NUM, UART_TX_PIN, UART_RX_PIN, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE);
    }

    void ARK::UART::SendString(const std::string& data) {
        uart_write_bytes(UART_NUM, data.c_str(), data.length());
    }

    bool ARK::UART::DataAvailable() {
        size_t length;
        uart_get_buffered_data_len(UART_NUM, &length);
        return length > 0;
    }

    uint8_t ARK::UART::ReceiveByte() {
        uint8_t data;
        uart_read_bytes(UART_NUM, &data, 1, portMAX_DELAY);
        return data;
    }
#elif defined(ARK_ARCH_SIL)
    #include <iostream>
    
    void ARK::UART::Setup(uint32_t baudrate) {
        SystemConsole.Print("[SIL_UART] Setup with baudrate: %d", baudrate);
    }

    void ARK::UART::SendString(const std::string& data) {
        SystemConsole.Print("[SIL_UART] Sending string: %s", data.c_str());
    }

    bool ARK::UART::DataAvailable() {
        // In a real simulation, you could check a buffer here
        return false;
    }

    uint8_t ARK::UART::ReceiveByte() {
        // In a real simulation, you could read from a buffer here
        return 0;
    }
#endif