#ifndef ARK_USER_KERNEL_HPP
#define ARK_USER_KERNEL_HPP

#include "../../../Ark.hpp"

namespace ARK {
    class UserKernel {
    public:
        static void Initialize();
        static void Execute(); 
    };
}

#endif