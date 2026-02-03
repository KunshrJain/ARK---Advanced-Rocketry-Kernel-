#ifndef SUPERIORLOOP_HPP
#define SUPERIORLOOP_HPP

#include <cstdint>

namespace ARK {
    class SuperiorLoop {
    public:
        static void Start(); 

    private:
        static constexpr uint32_t TARGET_FREQ_HZ = 400;
        static constexpr uint32_t TICK_PERIOD_US = 1000000 / TARGET_FREQ_HZ;
        
        static void Run(); 
    };
}

#endif