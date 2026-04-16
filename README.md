# Q.apk - Android Native Bypass & Hack Module

A high-performance Android native modification tool developed in C++ using the **KittyMemory** library. This project demonstrates advanced memory patching, pattern scanning, and bypass techniques for mobile gaming security systems (e.g., Xigncode).

---

## Features

* **Real-time Memory Patching**: Dynamically modify game instructions to enable features like No Recoil and No Spread.
* **Advanced Pattern Scanning**: Locate function addresses in memory using IDA-style patterns and symbol names.
* **Security Bypass**: Integrated logic to bypass integrity checks and security modules.
* **Real-time Ranking System**: High-performance logging system that tracks and displays the top 10 players based on RP (Rank Points).
* **Cross-Platform Core**: C++ backend optimized for `arm64-v8a` architecture.

---

## Technical Stack

* **Language**: C++ 17, Kotlin (for Android UI/Launcher)
* **Build System**: CMake, Gradle 8.0
* **NDK Version**: 25.1.8937393
* **Libraries**: 
    * [KittyMemory](https://github.com/MJ007/KittyMemory) - Used for runtime memory patching and memory maps.
    * **KittyScanner** - Custom implementation for symbol and pattern searching.

---

## Project Structure

* `app/src/main/cpp/`
    * `main.cpp`: Entry point for the native module and JNI bridge.
    * `modules/`: Contains specific hack logic (`Weapon.cpp`, `Aimbot.cpp`, `Esp.cpp`, `Bypass.cpp`).
    * `KittyMemory/`: Core memory manipulation utility.
    * `include/`: Header files and memory offsets (`offset.h`).
* `app/src/main/kotlin/`: Android launcher implementation.

---

## Build Instructions

This project is configured for automated builds via GitHub Actions or local Android Studio environments.

### Prerequisites
* Android SDK & NDK (v25.1+)
* CMake 3.22.1
* Gradle 8.0

### Local Build
```bash
./gradlew assembleDebug
