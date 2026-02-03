#include "Spi.hpp"
#include "ARK/HAL/Console/Console.hpp"

#ifdef ARK_ARCH_PICO
    #include "hardware/spi.h"
    #include "pico/stdlib.h"

    void ARK::SPI::Setup(uint32_t baudrate) {
        spi_init(spi_default, baudrate);
        gpio_set_function(PICO_DEFAULT_SPI_SCK_PIN, GPIO_FUNC_SPI);
        gpio_set_function(PICO_DEFAULT_SPI_TX_PIN, GPIO_FUNC_SPI);
        gpio_set_function(PICO_DEFAULT_SPI_RX_PIN, GPIO_FUNC_SPI);
    }

    void ARK::SPI::Transfer(uint8_t* tx, uint8_t* rx, uint16_t len) {
        spi_write_read_blocking(spi_default, tx, rx, len);
    }
#elif defined(ARK_ARCH_ESP32)
    #include "driver/spi_master.h"
    #include "driver/gpio.h"

    #define SPI_HOST SPI2_HOST
    #define PIN_NUM_MISO 19
    #define PIN_NUM_MOSI 23
    #define PIN_NUM_CLK  18

    static spi_device_handle_t spi_handle;

    void ARK::SPI::Setup(uint32_t baudrate) {
        spi_bus_config_t buscfg={
            .mosi_io_num=PIN_NUM_MOSI,
            .miso_io_num=PIN_NUM_MISO,
            .sclk_io_num=PIN_NUM_CLK,
            .quadwp_io_num=-1,
            .quadhd_io_num=-1,
            .max_transfer_sz=4094
        };
        spi_bus_initialize(SPI_HOST, &buscfg, SPI_DMA_CH_AUTO);

        spi_device_interface_config_t devcfg={
            .clock_speed_hz=baudrate,
            .mode=0,
            .spics_io_num=-1, // We manage CS manually
            .queue_size=1
        };
        spi_bus_add_device(SPI_HOST, &devcfg, &spi_handle);
    }

    void ARK::SPI::Transfer(uint8_t* tx, uint8_t* rx, uint16_t len) {
        if (len == 0) return;
        spi_transaction_t t;
        memset(&t, 0, sizeof(t));
        t.length = len * 8; // length in bits
        t.tx_buffer = tx;
        t.rx_buffer = rx;
        spi_device_polling_transmit(spi_handle, &t);
    }
#elif defined(ARK_ARCH_SIL)
    void ARK::SPI::Setup(uint32_t baudrate) {
        SystemConsole.Print("[SIL_SPI] Setup with baudrate: %d", baudrate);
    }

    void ARK::SPI::Transfer(uint8_t* tx, uint8_t* rx, uint16_t len) {
        SystemConsole.Print("[SIL_SPI] Transferring %d bytes.", len);
        // In a real simulation, you might want to model the behavior of a specific SPI device.
        for(uint16_t i = 0; i < len; ++i) rx[i] = i; // Fill with dummy data
    }
#endif