# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/kunsh/esp/esp-idf/components/bootloader/subproject"
  "/home/kunsh/Ignition/ARK/Build/Temp/Esp32/bootloader"
  "/home/kunsh/Ignition/ARK/Build/Temp/Esp32/bootloader-prefix"
  "/home/kunsh/Ignition/ARK/Build/Temp/Esp32/bootloader-prefix/tmp"
  "/home/kunsh/Ignition/ARK/Build/Temp/Esp32/bootloader-prefix/src/bootloader-stamp"
  "/home/kunsh/Ignition/ARK/Build/Temp/Esp32/bootloader-prefix/src"
  "/home/kunsh/Ignition/ARK/Build/Temp/Esp32/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/kunsh/Ignition/ARK/Build/Temp/Esp32/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/kunsh/Ignition/ARK/Build/Temp/Esp32/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
