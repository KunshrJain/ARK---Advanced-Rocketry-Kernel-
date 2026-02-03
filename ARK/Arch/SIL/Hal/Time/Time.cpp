#include "Time.hpp"
#include <thread>

namespace ARK {
    namespace HAL {
        namespace SIL {
            Time::Time() {
                startTime = std::chrono::high_resolution_clock::now();
            }

            uint64_t Time::GetMicros() {
                auto now = std::chrono::high_resolution_clock::now();
                return std::chrono::duration_cast<std::chrono::microseconds>(now - startTime).count();
            }

            void Time::DelayUntil(uint64_t target_us) {
                uint64_t now_us = GetMicros();
                if (target_us > now_us) {
                    std::this_thread::sleep_for(std::chrono::microseconds(target_us - now_us));
                }
            }

            void Time::SleepUs(uint64_t us) {
                std::this_thread::sleep_for(std::chrono::microseconds(us));
            }
        }
    }
}
