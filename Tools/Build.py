import os
import sys
import shutil
import subprocess
from SetupEnv import setup_pico, setup_esp32

def find_toolchain(sdk_path):
    """Recursively hunts for any valid ARM GCC toolchain file within the SDK."""
    # List of possible filenames in different SDK versions
    targets = ["pico_arm_gcc.cmake", "pico_arm_cortex_m0plus_gcc.cmake"]
    
    print(f"Scanning {sdk_path} for toolchain...")
    for root, dirs, files in os.walk(sdk_path):
        for file in files:
            if file in targets:
                found_path = os.path.join(root, file)
                print(f"Found toolchain: {found_path}")
                return found_path
    return None

def build_pico():
    sdk_path = setup_pico()
    temp_dir = os.path.abspath("Build/Temp/Pico")
    user_build_dir = os.path.abspath("Build/UserBuild")
    
    # Clean the build directory to avoid CMake cache issues
    if os.path.exists(temp_dir): 
        shutil.rmtree(temp_dir)
    os.makedirs(temp_dir, exist_ok=True)
    os.makedirs(user_build_dir, exist_ok=True)
    
    toolchain = find_toolchain(sdk_path)
    if not toolchain:
        print(f"Error: Could not locate a valid toolchain file in {sdk_path}")
        sys.exit(1)

    cmake_cmd = [
        "cmake", "-S", ".", "-B", temp_dir,
        f"-DPICO_SDK_PATH={sdk_path}",
        f"-DCMAKE_TOOLCHAIN_FILE={toolchain}",
        "-DPICO_BOARD=pico",
        "-G", "Unix Makefiles"
    ]
    
    print(f"--- Configuring ARK for Pico ---")
    subprocess.run(cmake_cmd, check=True)
    
    print("--- Building ARK Avionics ---")
    subprocess.run(["cmake", "--build", temp_dir, "-j"], check=True)
    
    # Final step: Move binary to UserBuild
    source = os.path.join(temp_dir, "ARK_Avionics.uf2")
    if os.path.exists(source):
        dest = os.path.join(user_build_dir, "ARK_Pico.uf2")
        shutil.copy(source, dest)
        print(f"\nSUCCESS: Binary moved to -> {dest}")

if __name__ == "__main__":
    target = sys.argv[1].lower() if len(sys.argv) > 1 else "pico"
    if target == "pico": 
        build_pico()

