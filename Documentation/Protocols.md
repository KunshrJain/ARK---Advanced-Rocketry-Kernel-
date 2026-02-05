# ARK Communication Protocols

The ARK library provides a unified interface for communication protocols (I2C, SPI, UART, GPIO) across different architectures (Raspberry Pi Pico, ESP32).

## Hardware Abstraction Layer (HAL)

ARK uses a HAL to decouple the protocol logic from the hardware implementation. This allows you to write your application code once and run it on different boards.

## Usage

### I2C

To use I2C, instantiate the `ARK::I2C` class with the desired port and pins.

```cpp
#include "ARK/System/CommunicationProtocols/I2c/I2c.hpp"

// Initialize I2C0 on Pico (SDA: GP4, SCL: GP5)
ARK::I2C myI2c(0, 4, 5);

void Setup() {
    myI2c.Begin(400000); // 400kHz
}

void Loop() {
    myI2c.Write(0x20, 0x10, 0xFF);
}
```

### SPI

```cpp
#include "ARK/System/CommunicationProtocols/Spi/Spi.hpp"

ARK::SPI mySpi(0, 16, 19, 18);

void Setup() {
    mySpi.Begin(1000000); // 1MHz
}
```

### UART

```cpp
#include "ARK/System/CommunicationProtocols/Uart/Uart.hpp"

ARK::UART myUart(0, 0, 1);

void Setup() {
    myUart.Begin(115200);
}

void Loop() {
    myUart.Write("Hello World!\n");
}
```

### GPIO

```cpp
#include "ARK/System/CommunicationProtocols/Gpio/Gpio.hpp"

ARK::GPIO led(25); // Onboard LED on Pico

void Setup() {
    led.Mode(ARK::HAL::PinMode::OUTPUT);
}

void Loop() {
    led.Toggle();
    // Delay...
}
```

## Supported Architectures

- **Raspberry Pi Pico (RP2040)**
- **ESP32** (Generic)
