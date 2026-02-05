#pragma once
#include <cstdint>
<<<<<<< HEAD
#include <string>
=======
#include <cstddef>
#include "ARK/HAL/Uart/Uart.hpp"
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)

namespace ARK {
    class UART {
    public:
<<<<<<< HEAD
        static void Setup(uint32_t baudrate);
        static void SendString(const std::string& data);
        static bool DataAvailable();
        static uint8_t ReceiveByte();
=======
        UART(uint8_t port_num, uint8_t tx_pin, uint8_t rx_pin);
        ~UART();

        void Begin(uint32_t baudrate);
        void Write(const uint8_t* data, size_t len);
        void Write(char c);
        void Write(const char* str);
        size_t Read(uint8_t* buffer, size_t len, uint32_t timeout_ms = 0);

    private:
        uint8_t _port_num;
        uint8_t _tx_pin;
        uint8_t _rx_pin;
        HAL::UART* _hal = nullptr;
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)
    };
}