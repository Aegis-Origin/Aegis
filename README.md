# Aegis
Aegis Engine

## Building with CMake

Requires Windows, CMake 3.20 or newer, and Visual Studio with the Desktop
development with C++ workload. Visual Studio 2026 requires CMake 4.2 or newer.
Run these commands from the repository root:

```powershell
git submodule update --init --recursive
cmake -S . -B build -A x64
cmake --build build --config Debug
.\build\bin\Debug\Sandbox.exe
```

Use `--config Release` to build Release instead. Aegis.dll and Sandbox.exe are
placed together under `build/bin/<configuration>`.

Sandbox currently logs initialization and then runs an infinite loop; stop it
with Ctrl+C in the terminal.

You can also open the repository folder in Visual Studio and select Sandbox as
the startup target. When adding engine source files, list them in CMakeLists.txt.
