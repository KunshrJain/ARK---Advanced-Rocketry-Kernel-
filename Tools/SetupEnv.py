import os
import subprocess
import platform
import shutil

def install_dependencies():
    """Peak Automation: Installs the ARM cross-compiler and build tools if missing."""
    if platform.system() == "Linux":
        # Check for essential tools: arm-none-eabi-gcc, make, and git
        deps_missing = not shutil.which("arm-none-eabi-gcc") or not shutil.which("make") or not shutil.which("git")
        if deps_missing:
            print("Required build tools missing. Installing system dependencies...")
            try:
                subprocess.run(["sudo", "apt", "update"], check=True)
                subprocess.run(["sudo", "apt", "install", "-y", 
                                "gcc-arm-none-eabi", "libnewlib-arm-none-eabi", 
                                "libstdc++-arm-none-eabi-newlib", "build-essential", "cmake", "git"], check=True)
            except subprocess.CalledProcessError:
                print("Warning: Failed to install dependencies automatically. Please run: sudo apt install build-essential gcc-arm-none-eabi")

def setup_pico():
    """Locates or downloads the Pico SDK and generates the CMake bridge file."""
    install_dependencies()
    
    # 1. Locate the SDK (Check Environment first, then standard paths)
    sdk_path = os.environ.get("PICO_SDK_PATH")
    if not sdk_path or not os.path.exists(sdk_path):
        target_dir = os.path.expanduser("~/.pico-sdk/sdk/2.2.0")
        if not os.path.exists(os.path.join(target_dir, "pico_sdk_init.cmake")):
            target_dir = os.path.expanduser("~/pico-sdk")
            if not os.path.exists(target_dir):
                print("Pico SDK not found. Automating download...")
                subprocess.run(f"git clone --recurse-submodules https://github.com/raspberrypi/pico-sdk.git {target_dir}", shell=True, check=True)
        sdk_path = target_dir

    # 2. Automatically generate/update the bridge file for the root CMakeLists.txt
    import_file = "pico_sdk_import.cmake"
    content = (
        "if (NOT PICO_SDK_PATH)\n"
        f"    set(PICO_SDK_PATH \"{sdk_path}\")\n"
        "endif ()\n"
        "include(${PICO_SDK_PATH}/pico_sdk_init.cmake)\n"
    )
    with open(import_file, "w") as f:
        f.write(content)
            
    return sdk_path

def setup_esp32():
    """Locates or downloads the ESP-IDF and executes installation scripts."""
    target_dir = os.path.expanduser("~/esp-idf")
    if not os.path.exists(target_dir):
        print("ESP-IDF not found. Automating download...")
        subprocess.run(f"git clone --recursive https://github.com/espressif/esp-idf.git {target_dir}", shell=True, check=True)
        
        # Run the SDK-specific installation script
        os.chdir(target_dir)
        install_cmd = "install.bat" if platform.system() == "Windows" else "./install.sh"
        subprocess.run(install_cmd, shell=True, check=True)
    return target_dir