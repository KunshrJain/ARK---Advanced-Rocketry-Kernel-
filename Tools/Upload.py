import os
import shutil
import platform
import getpass
import sys

def upload_pico():
    binary = "Build/UserBuild/ARK_Pico.uf2"
    if not os.path.exists(binary):
        print(f"Error: {binary} not found. Run Build.py first.")
        return

    pico_drive = None
    user = getpass.getuser()

    # Define likely mount points for WSL and Native Linux
    paths = [
        f"/media/{user}/RPI-RP2",
        f"/run/media/{user}/RPI-RP2",
        "/mnt/d", # WSL standard mount for D: drive
        "/mnt/e", # WSL standard mount for E: drive
        "/mnt/f",
        "/mnt/pico"
    ]

    for p in paths:
        if os.path.exists(p):
            # Verify it's actually a Pico by looking for the info file
            if os.path.exists(os.path.join(p, "INFO_UF2.TXT")):
                pico_drive = p
                break
    
    if pico_drive:
        print(f"Uploading to Pico found at {pico_drive}...")
        try:
            shutil.copy(binary, pico_drive)
            print("Upload Successful! Hardware should reboot now.")
        except Exception as e:
            print(f"Failed to copy: {e}")
    else:
        print("Pico not found in WSL. Have you mounted the drive?")
        print("Try: sudo mount -t drvfs D: /mnt/d  (Replace D: with your Pico's drive letter)")

if __name__ == "__main__":
    upload_pico()