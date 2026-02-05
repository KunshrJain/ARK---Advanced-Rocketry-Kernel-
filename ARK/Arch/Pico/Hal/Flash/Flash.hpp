#pragma once
#include "ARK/HAL/Flash/Flash.hpp"

namespace ARK {
    namespace HAL {
        namespace Pico {
            class Flash final : public HAL::Flash {
            public:
                void Initialize() override;
                void CommitShadow(ShadowRegistry data) override;
                ShadowRegistry RecoverShadow() override;
            };
        }
    }
}
