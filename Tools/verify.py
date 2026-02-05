import os
import subprocess
import sys
import time

def run_command(command, cwd=None):
    try:
        result = subprocess.run(
            command, 
            cwd=cwd, 
            shell=True, 
            check=True, 
            stdout=subprocess.PIPE, 
            stderr=subprocess.PIPE,
            text=True
        )
        return result.stdout.strip()
    except subprocess.CalledProcessError as e:
        print(f"Error running command: {command}")
        print(e.stderr)
        return None

def verify_sil():
    print("=== ARK Verification Protocol ===")
    project_root = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
    build_dir = os.path.join(project_root, "Build")
    
    # 1. Build SIL
    print("[1/3] Building SIL Target...")
    build_script = os.path.join(project_root, "Tools", "build.sh")
    if run_command(f"{build_script} -t SIL", cwd=project_root) is None:
        print("FAIL: Build failed.")
        sys.exit(1)
        
    # 2. Check Artifacts
    print("[2/3] Verifying Artifacts...")
    executable = os.path.join(build_dir, "ARK_Avionics_SIL")
    if not os.path.exists(executable):
        print(f"FAIL: Executable not found at {executable}")
        sys.exit(1)
        
    # 3. Runtime Verification
    print("[3/3] Running Simulation (5s Check)...")
    try:
        process = subprocess.Popen(
            [executable],
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
            cwd=project_root # Run from root so shadow.bin is found/created there
        )
        
        # Wait a bit to let it boot
        time.sleep(3)
        
        # We kill it, as it's an infinite loop
        process.terminate()
        try:
            outs, errs = process.communicate(timeout=1)
        except subprocess.TimeoutExpired:
            process.kill()
            outs, errs = process.communicate()
            
        print("--- Output Log ---")
        print(outs)
        print("------------------")
        
        if "[SYSTEM] System Kernel Initialized" in outs:
            print("SUCCESS: System Booted Successfully.")
        elif "[SHADOW]" in outs:
            print("SUCCESS: Shadow Registry Active.")
        else:
            print("WARNING: Expected boot messages not found. Check log.")
            sys.exit(1)

    except Exception as e:
        print(f"FAIL: Runtime error: {e}")
        sys.exit(1)

if __name__ == "__main__":
    verify_sil()
