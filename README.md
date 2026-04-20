# Kynto Engine v4.0

A modular, high-performance interpreter written in C, featuring a Micro-Kernel architecture with dynamic module loading.

## Key Features
* **Micro-Kernel:** Core logic under 100 lines of code.
* **Dynamic Linking:** Loads .so modules at runtime via dlopen/dlsym.
* **Modular Design:** Hardware, Math, and UI logic are completely decoupled.
* **Android Optimized:** Direct access to sysfs for battery and thermal monitoring.

## How to Build
1. Run `./build_kynto.sh` to compile the core and all modules.
2. Run scripts using `./kynto scripts/your_script.ky`.

## Example Script
```ky
module {./k_hw.so}
hw.battery
math.calc {50 + 50}
```
