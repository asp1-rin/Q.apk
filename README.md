# Q.apk: Native Memory Patching Demonstration

Q.apk is a Native Modding example project that directly modifies the runtime memory of Android games using the KittyMemory library.

## Key Features
- Library: KittyMemory (Memory Patching Tool)
- Method: Runtime Memory Patching & Offset Manipulation
- Implemented Modules:
    - Silent Aimbot: Forcing write operations on angle data within memory.
    - Wallhack/ESP: Visualizing entities by modifying rendering pipeline data.
    - Weapon Stabilization: Patching spread and recoil offsets using KittyMemory.

## Project Structure
- /jni: C++ source code based on KittyMemory.
- /src: Java/Kotlin code for UI and service management.
- /includes: Definitions for offsets and memory structures.

## Build Instructions
1. Install Android Studio.
2. Configure NDK (Native Development Kit).
3. Generate .so files and build via ndk-build or CMake.

## Disclaimer
This project is an open-source learning resource intended to help understand the memory structure of the Android OS. Unauthorized or malicious use is strongly discouraged.

## made by asp1-rin