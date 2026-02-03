#pragma once
#include "ARK/CoreTypes.hpp"

namespace ARK {
    namespace HAL {
        class Flash {
        public:
            virtual ~Flash() = default;
            virtual void Initialize() = 0;
            virtual void CommitShadow(ShadowRegistry data) = 0;
            virtual ShadowRegistry RecoverShadow() = 0;
        };
    }
    extern HAL::Flash& SystemFlash;
}
