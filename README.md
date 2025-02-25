# Libcrashd-dev

Libcrashd-dev is a **crash handling** library for **Linux** and **macOS** applications.
It provides crash dialogs, backtrace logging, and function validation for debugging purposes.

## Features
✅ **Crash dialog with GTK+3**


✅ **Error logging to `crashd.log`**


✅ **Backtrace generation**


✅ **Crash report generation**


✅ **Function validity checking**

## Installation

### **Linux (Debian/Ubuntu)**
```sh
sudo apt install libgtk-3-dev
```

### Linux (Arch)

```sh
sudo pacman -S gtk3
```

### macOS (Homebrew)

```sh
brew install gtk+3
```

## Build Instructions

Clone the repository and build it:

```bash
git clone https://github.com/Eduardo7881/Libcrashd-dev.git
cd libcrashd-dev
make
```

This will generate libcrashd.a on this project root
be sure to have libcrashd.h on your project root, so your app can find the lib.

Your project root can be like this:
```
├── src/
│   ├── myapp.cpp
├── include/
│   ├── libcrashd.h
├── lib/
│   ├── libcrashd.a
```

# Usage

Include Libcrashd-dev in your project:

```cpp
#include "libcrashd.h"
```

Compile your program with:

```bash
g++ -o myapp myapp.cpp libcrashd.a $(pkg-config --cflags --libs gtk+-3.0)
```

# Functions

## Crash Dialogue

```cpp
void Libcrashd::CrashDialogue(const std::string& title,
                              const std::string& message,
                              const std::string& footer);
```

📌 Creates a crash dialog and logs the error.

title → Window title (default: "This app crashed")

message → Error message (default: "This application hang and crashed.\nPlease restart.")

footer → Additional info (default: "Error: 0000-000")



---

## Crash Report

```cpp
void Libcrashd::GenerateCrashReport(const std::string& reason);
```

📌 Logs the crash reason with backtrace.


---

## Function Validation

```cpp
bool Libcrashd::IsFunctionValid(void* func);
```

📌 Checks if a function pointer is valid before calling.
Returns false and logs an error if func is nullptr.


---

## Backtrace

```cpp
std::string Libcrashd::GetBacktrace();
```

📌 Returns a backtrace of the current stack.


---

# License

MIT License. See LICENSE for details.
