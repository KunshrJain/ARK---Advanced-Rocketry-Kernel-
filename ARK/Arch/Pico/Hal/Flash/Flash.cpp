#include "Flash.hpp"
#include <cstring>
#include "hardware/flash.h"
#include "hardware/sync.h"

#define FLASH_TARGET_OFFSET (2048 * 1024 - FLASH_SECTOR_SIZE)
const uint8_t* flash_target_contents = (const uint8_t*)(XIP_BASE + FLASH_TARGET_OFFSET);

namespace ARK {
    namespace HAL {
        namespace Pico {
            void Flash::Initialize() {
            }

            void Flash::CommitShadow(ShadowRegistry data) {
                uint8_t buffer[FLASH_PAGE_SIZE];
                std::memset(buffer, 0, FLASH_PAGE_SIZE);
                std::memcpy(buffer, &data, sizeof(data));
                uint32_t ints = save_and_disable_interrupts();
                flash_range_erase(FLASH_TARGET_OFFSET, FLASH_SECTOR_SIZE);
                flash_range_program(FLASH_TARGET_OFFSET, buffer, FLASH_PAGE_SIZE);
                restore_interrupts(ints);
            }

            ShadowRegistry Flash::RecoverShadow() {
                ShadowRegistry data = {0, 0, 0, 0.0f, 0};
                std::memcpy(&data, flash_target_contents, sizeof(data));
                return data;
            }
        }
    }
}
