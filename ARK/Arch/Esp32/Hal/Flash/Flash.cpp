#include "Flash.hpp"
#include <cstring>
#include "nvs_flash.h"
#include "nvs.h"

namespace ARK {
    namespace HAL {
        namespace Esp32 {
            void Flash::Initialize() {
                esp_err_t ret = nvs_flash_init();
                if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
                    nvs_flash_erase();
                    nvs_flash_init();
                }
            }

            void Flash::CommitShadow(ShadowRegistry data) {
                nvs_handle_t handle;
                if (nvs_open("ark_shadow", NVS_READWRITE, &handle) == ESP_OK) {
                    nvs_set_blob(handle, "registry", &data, sizeof(data));
                    nvs_commit(handle);
                    nvs_close(handle);
                }
            }

            ShadowRegistry Flash::RecoverShadow() {
                ShadowRegistry data = {0, 0, 0, 0.0f, 0};
                nvs_handle_t handle;
                size_t size = sizeof(data);
                if (nvs_open("ark_shadow", NVS_READONLY, &handle) == ESP_OK) {
                    nvs_get_blob(handle, "registry", &data, &size);
                    nvs_close(handle);
                }
                return data;
            }
        }
    }
}
