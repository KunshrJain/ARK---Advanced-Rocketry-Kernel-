#pragma once
#include <cstdint>
#include <string>

namespace ARK {
    class UART {
    public:
        static void Setup(uint32_t baudrate);
        static void SendString(const std::string& data);
        static bool DataAvailable();
        static uint8_t ReceiveByte();
    };
}