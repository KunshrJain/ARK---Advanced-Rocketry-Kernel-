# CMakeLists for ARK ESP32 Component (Functions as Main)

# Include source definitions from root
include(${CMAKE_SOURCE_DIR}/ARK/sources.cmake)

# Prepare Absolute Paths for Sources
set(ABS_SOURCES "")
foreach(src ${ARK_COMMON_SOURCES})
    list(APPEND ABS_SOURCES "${CMAKE_SOURCE_DIR}/${src}")
endforeach()

# Prepare Absolute Paths for Includes
set(ABS_INCLUDES "")
foreach(inc ${ARK_COMMON_INCLUDE_DIRS})
    list(APPEND ABS_INCLUDES "${CMAKE_SOURCE_DIR}/${inc}")
endforeach()

# Specialized ESP32 HAL Sources
file(GLOB_RECURSE ESP_HAL_SOURCES "Hal/*.cpp")

# Specialized Includes
list(APPEND ABS_INCLUDES 
    "Hal"
    "Hal/Time"
    "Hal/Clock"
    "Hal/Console"
    "Hal/Flash"
    "Hal/Gpio"
    "Hal/I2c"
    "Hal/Spi"
    "Hal/Uart"
)

idf_component_register(
    SRCS 
        "Entry.cpp"
        ${ESP_HAL_SOURCES}
        ${ABS_SOURCES}
    INCLUDE_DIRS 
        ${ABS_INCLUDES}
    REQUIRES
        nvs_flash
        driver
        esp_timer
        esp_common
        log
        freertos
)
