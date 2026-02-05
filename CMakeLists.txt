cmake_minimum_required(VERSION 3.16)

# 1. Architecture Detection
<<<<<<< HEAD
option(ARCH_TARGET "Auto" "Target architecture (PICO, ESP32, SIL)")
=======
set(ARCH_TARGET "Auto" CACHE STRING "Target architecture (PICO, ESP32, SIL)")
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)

if(ARCH_TARGET STREQUAL "Auto")
    if(DEFINED ENV{IDF_PATH})
        set(ARCH_TARGET "ESP32")
    else()
        set(ARCH_TARGET "PICO")
    endif()
endif()

message(STATUS "ARK Architecture Target: ${ARCH_TARGET}")

if(ARCH_TARGET STREQUAL "ESP32")
    include($ENV{IDF_PATH}/tools/cmake/project.cmake)
    project(ARK_Avionics)
elseif(ARCH_TARGET STREQUAL "PICO")
<<<<<<< HEAD
    project(ARK_Avionics C CXX ASM)
    include(pico_sdk_import.cmake)
    pico_sdk_init()
else()
    project(ARK_Avionics CXX)
endif()

# 2. Universal Source Files
set(ARK_SOURCES
    "ARK/Ark.cpp"
    "ARK/Kernel/Loops/SuperiorLoop.cpp"
    "ARK/Kernel/MicroKernels/ModulesKernel/ModulesKernel.cpp"
    "ARK/Kernel/MicroKernels/SystemKernel/SystemKernel.cpp"
    "ARK/Kernel/MicroKernels/UserKernel/UserKernel.cpp"
    "ARK/Kernel/StateMachine/States.cpp"
    "ARK/System/Time/Time.cpp"
    "ARK/System/Clock/Clock.cpp"
    "ARK/System/Console/Console.cpp"
    "ARK/System/Storage/Storage.cpp"
    "Modules/ModulesManager.cpp"
    "User/UserCode.cpp"
    "User/UserTransitions.cpp"
    "ARK/System/CommunicationProtocols/Gpio/Gpio.cpp"
    "ARK/System/CommunicationProtocols/I2c/I2c.cpp"
    "ARK/System/CommunicationProtocols/Spi/Spi.cpp"
    "ARK/System/CommunicationProtocols/Uart/Uart.cpp"
    "ARK/System/Power/Power.cpp"
    "ARK/System/FDIR/FDIR.cpp"
=======
    include(${CMAKE_SOURCE_DIR}/Build/pico_sdk_import.cmake)
    project(ARK_Avionics C CXX ASM)
    pico_sdk_init()
    
    add_compile_options(-ffunction-sections -fdata-sections)
    add_link_options(-Wl,--gc-sections)
else()
    project(ARK_Avionics CXX)
    add_compile_options(-ffunction-sections -fdata-sections)
    add_link_options(-Wl,--gc-sections)
endif()

# 2. Universal Source Files
set(SOURCES
    ARK/Ark.cpp
    ARK/Kernel/Loops/SuperiorLoop.cpp
    ARK/Kernel/StateMachine/States.cpp
    
    # MicroKernels
    ARK/Kernel/MicroKernels/ModulesKernel/ModulesKernel.cpp
    ARK/Kernel/MicroKernels/SystemKernel/SystemKernel.cpp
    ARK/Kernel/MicroKernels/UserKernel/UserKernel.cpp
    
    # System Components
    ARK/System/FDIR/FDIR.cpp
    ARK/System/Storage/Storage.cpp
    ARK/System/Console/Console.cpp
    ARK/System/Time/Time.cpp
    ARK/System/Clock/Clock.cpp
    ARK/System/Power/Power.cpp
    ARK/System/CommunicationProtocols/Gpio/Gpio.cpp
    ARK/System/CommunicationProtocols/I2c/I2c.cpp
    ARK/System/CommunicationProtocols/Spi/Spi.cpp
    ARK/System/CommunicationProtocols/Uart/Uart.cpp

    # Modules
    Modules/ModulesManager.cpp
    Modules/WS2812/WS2812.cpp

    # User Code
    User/UserCode.cpp
    User/UserTransitions.cpp
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)
)

# 3. Target Specific Execution
if(ARCH_TARGET STREQUAL "PICO")
    add_definitions(-DARK_ARCH_PICO)
<<<<<<< HEAD
    add_executable(ARK_Avionics ${ARK_SOURCES} "ARK/Arch/Pico/Entry.cpp" "ARK/Arch/Pico/Hal/Clock/Clock.cpp" "ARK/Arch/Pico/Hal/Console/Console.cpp" "ARK/Arch/Pico/Hal/Flash/Flash.cpp" "ARK/Arch/Pico/Hal/Time/Time.cpp")

    target_include_directories(ARK_Avionics PUBLIC 
        . 
=======
    add_executable(ARK_Avionics ${SOURCES} "ARK/Arch/Pico/Entry.cpp" "ARK/Arch/Pico/Hal/Clock/Clock.cpp" "ARK/Arch/Pico/Hal/Console/Console.cpp" "ARK/Arch/Pico/Hal/Flash/Flash.cpp" "ARK/Arch/Pico/Hal/Time/Time.cpp")

    pico_generate_pio_header(ARK_Avionics ${CMAKE_SOURCE_DIR}/Modules/WS2812/ws2812.pio)
    
    target_include_directories(ARK_Avionics PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
    target_include_directories(ARK_Avionics PUBLIC 
        . 
        ${CMAKE_CURRENT_BINARY_DIR}
        ${CMAKE_CURRENT_SOURCE_DIR}/Build 
        ${PICO_SDK_PATH}/src/rp2_common/hardware_adc/include
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)
        ARK
        ARK/HAL
        ARK/Arch/Pico/Hal
        ARK/Arch/Pico/Hal/Time
        ARK/Arch/Pico/Hal/Clock
        ARK/Arch/Pico/Hal/Console
        ARK/Arch/Pico/Hal/Flash 
        ARK/Kernel/Loops
        ARK/Kernel/MicroKernels/ModulesKernel
        ARK/Kernel/MicroKernels/SystemKernel
        ARK/Kernel/MicroKernels/UserKernel
        ARK/Kernel/StateMachine
        Modules
        User
        ARK/System/CommunicationProtocols/Gpio
        ARK/System/CommunicationProtocols/I2c
        ARK/System/CommunicationProtocols/Spi
        ARK/System/CommunicationProtocols/Uart
        ARK/System/Power
        ARK/System/FDIR
    )
    
    target_link_libraries(ARK_Avionics 
        pico_stdlib 
        hardware_clocks 
        hardware_vreg
        hardware_i2c
        hardware_spi
        hardware_uart
        hardware_flash
<<<<<<< HEAD
=======
        hardware_adc
        hardware_pio
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)
    )
    pico_add_extra_outputs(ARK_Avionics)

elseif(ARCH_TARGET STREQUAL "ESP32")
    add_definitions(-DARK_ARCH_ESP32)
<<<<<<< HEAD
    idf_component_register(SRCS ${ARK_SOURCES} "ARK/Arch/Esp32/Entry.cpp" "ARK/Arch/Esp32/Hal/Clock/Clock.cpp" "ARK/Arch/Esp32/Hal/Console/Console.cpp" "ARK/Arch/Esp32/Hal/Flash/Flash.cpp" "ARK/Arch/Esp32/Hal/Time/Time.cpp"
                           INCLUDE_DIRS 
                           "." "ARK" "ARK/HAL" "ARK/Arch/Esp32/Hal" "ARK/Arch/Esp32/Hal/Time" "ARK/Arch/Esp32/Hal/Clock" "ARK/Arch/Esp32/Hal/Console" "ARK/Arch/Esp32/Hal/Flash"
                           "Modules" "User"
                           "ARK/Kernel/Loops" "ARK/Kernel/StateMachine"
                           "ARK/Kernel/MicroKernels/ModulesKernel"
                           "ARK/Kernel/MicroKernels/SystemKernel"
                           "ARK/Kernel/MicroKernels/UserKernel"
                           "ARK/System/CommunicationProtocols/Gpio"
                           "ARK/System/CommunicationProtocols/I2c"
                           "ARK/System/CommunicationProtocols/Spi"
                           "ARK/System/CommunicationProtocols/Uart"
                           "ARK/System/Power"
                           "ARK/System/FDIR")
=======
    # The 'main' component in ./main/CMakeLists.txt handles the registration
    idf_build_set_property(COMPILE_OPTIONS "-ffunction-sections" "-fdata-sections" APPEND)
    idf_build_set_property(LINK_OPTIONS "-Wl,--gc-sections" APPEND)
>>>>>>> 452b8f4 (Re-initialized repository with clean .gitignore and synced structure)

elseif(ARCH_TARGET STREQUAL "SIL")
    add_definitions(-DARK_ARCH_SIL)
    add_executable(ARK_Avionics_SIL ${ARK_SOURCES} 
        "ARK/Arch/SIL/Entry.cpp"
        "ARK/Arch/SIL/Hal/Clock/Clock.cpp" 
        "ARK/Arch/SIL/Hal/Console/Console.cpp" 
        "ARK/Arch/SIL/Hal/Flash/Flash.cpp"
        "ARK/Arch/SIL/Hal/Time/Time.cpp"
    )

    target_include_directories(ARK_Avionics_SIL PUBLIC 
        . 
        ARK
        ARK/HAL
        ARK/Arch/SIL/Hal
        ARK/Arch/SIL/Hal/Time
        ARK/Arch/SIL/Hal/Clock
        ARK/Arch/SIL/Hal/Console
        ARK/Arch/SIL/Hal/Flash 
        ARK/Kernel/Loops
        ARK/Kernel/MicroKernels/ModulesKernel
        ARK/Kernel/MicroKernels/SystemKernel
        ARK/Kernel/MicroKernels/UserKernel
        ARK/Kernel/StateMachine
        Modules
        User
        ARK/System/CommunicationProtocols/Gpio
        ARK/System/CommunicationProtocols/I2c
        ARK/System/CommunicationProtocols/Spi
        ARK/System/CommunicationProtocols/Uart
        ARK/System/Power
        ARK/System/FDIR
    )
endif()