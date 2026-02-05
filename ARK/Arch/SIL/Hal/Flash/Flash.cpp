#include "Flash.hpp"
#include <fstream>

namespace ARK {
    namespace HAL {
        namespace SIL {
            static const char* SHADOW_FILE = "shadow.bin";

            void Flash::Initialize() {
            }

            void Flash::CommitShadow(ShadowRegistry data) {
                std::ofstream file(SHADOW_FILE, std::ios::binary | std::ios::trunc);
                if (file.is_open()) {
                    file.write(reinterpret_cast<const char*>(&data), sizeof(data));
                    file.close();
                }
            }

            ShadowRegistry Flash::RecoverShadow() {
                ShadowRegistry data = {0, 0, 0, 0.0f, 0};
                std::ifstream file(SHADOW_FILE, std::ios::binary);
                if (file.is_open()) {
                    file.read(reinterpret_cast<char*>(&data), sizeof(data));
                    file.close();
                }
                return data;
            }
        }
    }
}
