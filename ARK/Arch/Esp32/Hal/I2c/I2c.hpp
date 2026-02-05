#pragma once
#include "ARK/HAL/I2c/I2c.hpp"
#include "driver/i2c.h"

namespace ARK {
    namespace HAL {
        namespace Esp32 {
            class I2C : public ARK::HAL::I2C {
            public:
                void Init(uint8_t port_num, uint8_t sda_pin, uint8_t scl_pin, uint32_t baudrate) override {
                    _port = (port_num == 0) ? I2C_NUM_0 : I2C_NUM_1;
                    
                    i2c_config_t conf = {};
                    conf.mode = I2C_MODE_MASTER;
                    conf.sda_io_num = (gpio_num_t)sda_pin;
                    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
                    conf.scl_io_num = (gpio_num_t)scl_pin;
                    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
                    conf.master.clk_speed = baudrate;
                    conf.clk_flags = 0;
                    i2c_param_config(_port, &conf);
                    i2c_driver_install(_port, conf.mode, 0, 0, 0);
                }

                bool Write(uint8_t addr, uint8_t reg, uint8_t data) override {
                    uint8_t write_buf[] = {reg, data};
                    esp_err_t err = i2c_master_write_to_device(_port, addr, write_buf, sizeof(write_buf), 1000 / portTICK_PERIOD_MS);
                    return err == ESP_OK;
                }

                bool Write(uint8_t addr, uint8_t* data, size_t len) override {
                    esp_err_t err = i2c_master_write_to_device(_port, addr, data, len, 1000 / portTICK_PERIOD_MS);
                    return err == ESP_OK;
                }

                bool Read(uint8_t addr, uint8_t reg, uint8_t* buffer, size_t len) override {
                    esp_err_t err = i2c_master_write_read_device(_port, addr, &reg, 1, buffer, len, 1000 / portTICK_PERIOD_MS);
                    return err == ESP_OK;
                }

                bool Read(uint8_t addr, uint8_t* buffer, size_t len) override {
                    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
                    i2c_master_start(cmd);
                    i2c_master_write_byte(cmd, (addr << 1) | I2C_MASTER_READ, true);
                    if (len > 1) {
                         i2c_master_read(cmd, buffer, len - 1, I2C_MASTER_ACK);
                    }
                    i2c_master_read_byte(cmd, buffer + len - 1, I2C_MASTER_NACK);
                    i2c_master_stop(cmd);
                    esp_err_t err = i2c_master_cmd_begin(_port, cmd, 1000 / portTICK_PERIOD_MS);
                    i2c_cmd_link_delete(cmd);
                    return err == ESP_OK;
                }

            private:
                i2c_port_t _port;
            };
        }
    }
}
