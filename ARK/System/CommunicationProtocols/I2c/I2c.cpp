#include "I2c.hpp"
<<<<<<< HEAD
#include "ARK/HAL/Console/Console.hpp"

#ifdef ARK_ARCH_PICO
    #include "pico/stdlib.h"
    #include "hardware/i2c.h"

    void ARK::I2C::Setup(uint32_t baudrate) {
        i2c_init(i2c_default, baudrate);
        gpio_set_function(PICO_DEFAULT_I2C_SDA_PIN, GPIO_FUNC_I2C);
        gpio_set_function(PICO_DEFAULT_I2C_SCL_PIN, GPIO_FUNC_I2C);
        gpio_pull_up(PICO_DEFAULT_I2C_SDA_PIN);
        gpio_pull_up(PICO_DEFAULT_I2C_SCL_PIN);
    }

    bool ARK::I2C::Write(uint8_t addr, uint8_t reg, uint8_t data) {
        uint8_t buf[] = {reg, data};
        return i2c_write_blocking(i2c_default, addr, buf, 2, false) == 2;
    }

    bool ARK::I2C::Read(uint8_t addr, uint8_t reg, uint8_t* buffer, uint16_t len) {
        i2c_write_blocking(i2c_default, addr, &reg, 1, true);
        return i2c_read_blocking(i2c_default, addr, buffer, len, false) == len;
    }
#elif defined(ARK_ARCH_ESP32)
    #include "driver/i2c.h"

    #define I2C_MASTER_SCL_IO 22
    #define I2C_MASTER_SDA_IO 21
    #define I2C_MASTER_NUM I2C_NUM_0
    #define I2C_MASTER_TX_BUF_DISABLE 0
    #define I2C_MASTER_RX_BUF_DISABLE 0

    void ARK::I2C::Setup(uint32_t baudrate) {
        i2c_config_t conf;
        conf.mode = I2C_MODE_MASTER;
        conf.sda_io_num = I2C_MASTER_SDA_IO;
        conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
        conf.scl_io_num = I2C_MASTER_SCL_IO;
        conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
        conf.master.clk_speed = baudrate;
        conf.clk_flags = 0;
        i2c_param_config(I2C_MASTER_NUM, &conf);
        i2c_driver_install(I2C_MASTER_NUM, conf.mode, I2C_MASTER_RX_BUF_DISABLE, I2C_MASTER_TX_BUF_DISABLE, 0);
    }

    bool ARK::I2C::Write(uint8_t addr, uint8_t reg, uint8_t data) {
        uint8_t write_buf[] = {reg, data};
        esp_err_t err = i2c_master_write_to_device(I2C_MASTER_NUM, addr, write_buf, sizeof(write_buf), 1000 / portTICK_PERIOD_MS);
        return err == ESP_OK;
    }

    bool ARK::I2C::Read(uint8_t addr, uint8_t reg, uint8_t* buffer, uint16_t len) {
        esp_err_t err = i2c_master_write_read_device(I2C_MASTER_NUM, addr, &reg, 1, buffer, len, 1000 / portTICK_PERIOD_MS);
        return err == ESP_OK;
    }
#elif defined(ARK_ARCH_SIL)
    void ARK::I2C::Setup(uint32_t baudrate) {
        SystemConsole.Print("[SIL_I2C] Setup with baudrate: %d", baudrate);
    }

    bool ARK::I2C::Write(uint8_t addr, uint8_t reg, uint8_t data) {
        SystemConsole.Print("[SIL_I2C] Write to addr: 0x%02X, reg: 0x%02X, data: 0x%02X", addr, reg, data);
        return true;
    }

    bool ARK::I2C::Read(uint8_t addr, uint8_t reg, uint8_t* buffer, uint16_t len) {
        SystemConsole.Print("[SIL_I2C] Read from addr: 0x%02X, reg: 0x%02X, len: %d", addr, reg, len);
        for(uint16_t i = 0; i < len; ++i) buffer[i] = i; // Fill with dummy data
        return true;
    }
#endif
=======
#include "Config.hpp"

#ifdef ARK_ARCH_PICO
#include "ARK/Arch/Pico/Hal/I2c/I2c.hpp"
#elif defined(ARK_ARCH_ESP32)
#include "ARK/Arch/Esp32/Hal/I2c/I2c.hpp"
#endif

namespace ARK {

    I2C::I2C(uint8_t port_num, uint8_t sda_pin, uint8_t scl_pin) 
        : _port_num(port_num), _sda_pin(sda_pin), _scl_pin(scl_pin) {
        #ifdef ARK_ARCH_PICO
            _hal = new HAL::Pico::I2C();
        #elif defined(ARK_ARCH_ESP32)
            _hal = new HAL::Esp32::I2C();
        #endif
    }

    I2C::~I2C() {
        if (_hal) delete _hal;
    }

    void I2C::Begin(uint32_t baudrate) {
        if (_hal) _hal->Init(_port_num, _sda_pin, _scl_pin, baudrate);
    }

    bool I2C::Write(uint8_t addr, uint8_t reg, uint8_t data) {
        if (_hal) return _hal->Write(addr, reg, data);
        return false;
    }

    bool I2C::Write(uint8_t addr, uint8_t* data, size_t len) {
        if (_hal) return _hal->Write(addr, data, len);
        return false;
    }

    bool I2C::Read(uint8_t addr, uint8_t reg, uint8_t* buffer, size_t len) {
        if (_hal) return _hal->Read(addr, reg, buffer, len);
        return false;
    }

    bool I2C::Read(uint8_t addr, uint8_t* buffer, size_t len) {
        if (_hal) return _hal->Read(addr, buffer, len);
        return false;
    }
}
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)
