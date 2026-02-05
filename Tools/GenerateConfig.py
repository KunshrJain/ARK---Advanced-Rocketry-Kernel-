import os

CONFIG_FILE = "Config.hpp"
DEFAULT_CONFIG = {
    # Boolean values
    "IS_BATTERY": False,
    "IS_FILTERS": False,
    "USE_STATE_BOOT": True,
    "USE_STATE_INITIALIZING": True,
    "USE_STATE_CALIBRATION": True,
    "USE_STATE_IDLE": True,
    "USE_STATE_PRE_ARM": True,
    "USE_STATE_ARMED": True,
    "USE_STATE_LAUNCH": True,
    "USE_STATE_ASCENT": True,
    "USE_STATE_BURNOUT": True,
    "USE_STATE_SEPARATION": True,
    "USE_STATE_CRUISING": True,
    "USE_STATE_COASTING": True,
    "USE_STATE_APOGEE": True,
    "USE_STATE_DROGUE_DESCENT": True,
    "USE_STATE_MAIN_DESCENT": True,
    "USE_STATE_TOUCHDOWN": True,
    "USE_STATE_LANDED": True,
    "USE_STATE_TEST_MODE": False,
    "USE_STATE_ABORT": True,
    "ENABLE_SD_LOGGING": True,
    "USE_BUZZER": True,

    # Integer values
    "MCU_FREQUENCY_MHZ": 200,
    "SYSTEM_FREQUENCY_HZ": 400,
    "MODULES_KERNEL_FREQUENCY": 200,
    "SYSTEM_KERNEL_FREQUENCY": 300,
    "USER_KERNEL_FREQUENCY": 200,
    "KERNEL_GUARD_US": 500
}

def read_config():
    config = DEFAULT_CONFIG.copy()
    if not os.path.exists(CONFIG_FILE):
        return config
    
    with open(CONFIG_FILE, "r") as f:
        for line in f:
            if line.startswith("#define"):
                parts = line.split()
                if len(parts) >= 3:
                    key = parts[1]
                    value_str = parts[2].replace(";", "")
                    
                    if value_str.lower() == "true":
                        config[key] = True
                    elif value_str.lower() == "false":
                        config[key] = False
                    elif value_str.isdigit():
                        config[key] = int(value_str)
    return config

def write_config(config):
    with open(CONFIG_FILE, "w") as f:
        f.write("#pragma once\n\n")
        f.write("// ARK System Configuration\n\n")
        
        for key, value in config.items():
            if isinstance(value, bool):
                val_str = "true" if value else "false"
            else:
                val_str = str(value)
            
            f.write(f"#define {key} {val_str}\n")
    print(f"Updated {CONFIG_FILE}")

def display_menu(config):
    keys = list(config.keys())
    print("\n--- ARK Configuration Manager ---")
    for i, key in enumerate(keys):
        print(f"{i+1}. {key} = {config[key]}")
    print("0. Save and Exit")
    return keys

def main():
    config = read_config()
    
    while True:
        keys = display_menu(config)
        try:
            choice = int(input("> "))
        except ValueError:
            continue
            
        if choice == 0:
            write_config(config)
            break
        
        if 1 <= choice <= len(keys):
            key = keys[choice-1]
            current_val = config[key]
            
            if isinstance(current_val, bool):
                config[key] = not current_val
            else:
                try:
                    new_val = int(input(f"Enter new value for {key}: "))
                    config[key] = new_val
                except ValueError:
                    print("Invalid number")

if __name__ == "__main__":
    main()
