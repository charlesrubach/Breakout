# Breakout Game

A modern implementation of the classic breakout/brick-breaker game written in C using the [raylib](https://www.raylib.com/) library. This project showcases a clean, modular architecture with multiple game screens and states.

## Features

- **Modular Architecture**: Organized screen-based system with separate game states (Logo, Title, Gameplay, Ending)
- **Cross-Platform Build Support**: Compiles on Windows with MinGW or Visual Studio 2022/2026
- **Modern Build System**: Uses premake5 for build configuration and automatic Makefile generation
- **Fast Performance**: Runs at 60 FPS with a fixed 800×450 window resolution
- **Structured Code**: Separation of concerns with dedicated header files and screen modules

## Project Structure

```
breakout/
├── src/                          # Source code
│   ├── breakout.c               # Main entry point
│   ├── game.c & game.h          # Core game logic and state management
│   ├── application.rc           # Windows resource file
│   └── screens/                 # Game screen modules
│       ├── logo.c & logo.h      # Logo/splash screen
│       └── title.c & title.h    # Title menu screen
├── include/                      # Header files
│   ├── config.h                 # Game configuration (resolution, FPS)
│   ├── game.h                   # Game structure definitions
│   ├── resource_dir.h           # Resource directory utilities
│   └── screens/                 # Screen header files
├── build/                        # Build system files
│   ├── premake5.lua             # Build configuration
│   └── premake5.exe             # Build tool
├── bin/                          # Compiled binaries
│   ├── Debug/                   # Debug build output
│   └── Release/                 # Release build output
├── obj/                          # Object files and intermediate build artifacts
└── Makefile                      # Generated makefile (created by premake5)
```

## Requirements

- **Windows OS** (MinGW or Visual Studio 2022/2026)
- **raylib** (included in the project under `build/external/raylib-master/`)
- **Build Tools**:
  - **MinGW**: mingw32-make and gcc compiler
  - **Visual Studio 2022/2026**: msvc compiler
- **premake5**: Provided in the build directory

## Building

### Option 1: MinGW (Command Line)

```bash
# Using the provided batch script
./build-MinGW-W64.bat

# Or manually with make
mingw32-make.exe
```

### Option 2: Visual Studio 2022

```bash
./build-VisualStudio2022.bat
```

### Option 3: Visual Studio 2026

```bash
./build-VisualStudio2026.bat
```

### Build Targets

Use these targets with `mingw32-make`:

```bash
# Debug build (default)
mingw32-make.exe

# Release build with optimizations
mingw32-make.exe config=release_x64

# Clean build artifacts
mingw32-make.exe clean

# Update makefiles from premake configuration
./build/premake5.exe gmake
```

## Running the Game

After building, find the executable in `bin/Debug/` or `bin/Release/`:

```bash
# Debug version
./bin/Debug/breakout.exe

# Release version
./bin/Release/breakout.exe
```

## Game States

The game progresses through several states:

1. **SHOW_LOGO** - Initial splash screen with logo
2. **SHOW_TITLE** - Main title/menu screen
3. **SHOW_GAMEPLAY** - Active gameplay (breakout game)
4. **SHOW_ENDING** - End screen (victory/game over)

## Configuration

Game settings can be modified in [include/config.h](include/config.h):

```c
static int SCREEN_WIDTH = 800;
static int SCREEN_HEIGHT = 450;
static int TARGET_FPS = 60;
```

## Development

### Key Files

- [src/breakout.c](src/breakout.c) - Main entry point with window initialization and game loop
- [src/game.c](src/game.c) - Game state management and update/render logic
- [build/premake5.lua](build/premake5.lua) - Build configuration for all platforms

### Screen Implementation

Each game screen (logo, title, gameplay, ending) follows a consistent pattern:

1. **Init**: Initialize resources and state
2. **Update**: Handle input and logic
3. **Render**: Draw to screen
4. **Unload**: Clean up resources

## Technologies

- **raylib** - Simple and easy-to-use graphics library
- **C** - Core implementation language
- **premake5** - Cross-platform build configuration
- **MinGW/MSVC** - Compilers

## License

This project uses raylib, which is licensed under the zlib license. See [build/external/raylib-master/LICENSE](build/external/raylib-master/LICENSE) for details.

## Resources

- [raylib Documentation](https://www.raylib.com/docs)
- [raylib Examples](https://github.com/raysan5/raylib/tree/master/examples)
- [premake5 Documentation](https://github.com/premake/premake-core/wiki)
