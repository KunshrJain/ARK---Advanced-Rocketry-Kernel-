#pragma once
#include "ARK/HAL/Spi/Spi.hpp"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include <string.h>

namespace ARK {
    namespace HAL {
        namespace Esp32 {
            class SPI : public ARK::HAL::SPI {
            public:
                void Init(uint8_t port_num, uint8_t miso_pin, uint8_t mosi_pin, uint8_t sck_pin, uint32_t baudrate) override {
                    _host = (port_num == 1) ? SPI3_HOST : SPI2_HOST;
                    
                    spi_bus_config_t buscfg = {};
                    buscfg.mosi_io_num = (gpio_num_t)mosi_pin;
                    buscfg.miso_io_num = (gpio_num_t)miso_pin;
                    buscfg.sclk_io_num = (gpio_num_t)sck_pin;
                    buscfg.quadwp_io_num = -1;
                    buscfg.quadhd_io_num = -1;
                    buscfg.max_transfer_sz = 4094;
                    
                    spi_bus_initialize(_host, &buscfg, SPI_DMA_CH_AUTO);

                    spi_device_interface_config_t devcfg = {};
                    devcfg.clock_speed_hz = (int)baudrate;
                    devcfg.mode = 0;
                    devcfg.spics_io_num = -1; 
                    devcfg.queue_size = 1;
                    spi_bus_add_device(_host, &devcfg, &_handle);
                }

                void Transfer(uint8_t* tx, uint8_t* rx, size_t len) override {
                    if (len == 0) return;
                    spi_transaction_t t;
                    memset(&t, 0, sizeof(t));
                    t.length = len * 8; 
                    t.tx_buffer = tx;
                    t.rx_buffer = rx;
                    spi_device_polling_transmit(_handle, &t);
                }

                void Write(uint8_t* data, size_t len) override {
                    Transfer(data, nullptr, len);
                }

            private:
                spi_host_device_t _host;
                spi_device_handle_t _handle;
            };
        }
    }
}
