#include "UserKernel.hpp"
#include "ARK/UserAPI/UserCode.hpp"
#include "ARK/Kernel/Loops/SuperiorLoop.hpp" // To access the static shadow if exposed

namespace ARK {
    void UserKernel::Initialize() {
        UserSetup(); // Calls your User Setup
    }

    void UserKernel::Execute() {
        UserLoop();  // Calls your User Loop
    }
}