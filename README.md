# Digit AI

Lightweight C project that demonstrates a small neural network to recognize handwritten
digits (MNIST-style) and a minimal graphical demo using raylib.

**Key points:** trains/evaluates on CSV-formatted MNIST data and provides a simple
visualization front-end.

**Repository:** [README.md](README.md)

## Features
- Small feed-forward neural network implementation in plain C
- Data loader for MNIST CSV files (`assets/mnist_train.csv`, `assets/mnist_test.csv`)
- Minimal interactive demo using `raylib` (windowed canvas to draw digits)

## Requirements
- C compiler (MSVC/clang/gcc)
- CMake 3.15+ and a build tool (Visual Studio, Ninja, or Make)
- `raylib` (the project includes a subproject configuration; CMake will populate or
	expect an existing installation)

On Windows with Visual Studio the repository already contains a CMake-based build
in `build/` created by the IDE. For other platforms or clean builds follow the
steps below.

## Build (cross-platform)

Shell (recommended for Unix / MinGW):

```sh
cmake -S . -B build
cmake --build build --config Release
```

Windows (Visual Studio generator):

```powershell
mkdir build; cd build
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

Notes:
- The first configure may download or configure the `raylib` subproject under
	`build/_deps/` — allow network access if prompted.

## Run

After building the executable (target name: `digit-ai`) run it from the build
folder or from the IDE configuration. Example paths:

```powershell
# Release build on Windows
.\build\Release\digit-ai.exe

# Or from a Unix-style build directory
./build/digit-ai
```

When launched the program will either run a training/evaluation routine or open
the interactive canvas depending on build flags and available dataset files.

## Data
- Training and test CSVs are in [assets/mnist_train.csv](assets/mnist_train.csv)
	and [assets/mnist_test.csv](assets/mnist_test.csv).
- CSV format: each row is `label,pixel0,pixel1,...,pixel783` (0–255). The code
	includes a loader in `src/mnist.c` that normalizes pixels; adjust normalization
	in `src/` if needed.

## Project layout
- [CMakeLists.txt](CMakeLists.txt) — build configuration
- [src/main.c](src/main.c) — program entry
- [src/nn.c](src/nn.c) — neural network implementation
- [src/mnist.c](src/mnist.c) — CSV loader / dataset utilities
- [src/app.c](src/app.c), [src/canvas.c](src/canvas.c) — demo UI and drawing code
- [include/](include/) — public headers for the modules
- [assets/](assets/) — example MNIST CSVs used by the demo

## Development notes
- To experiment with network topology, edit `include/nn.h` and `src/nn.c`.
- To swap datasets, replace the CSV files in `assets/` or point the loader at
	your own dataset.
- The project currently has no explicit license file. Add a `LICENSE` if you
	intend to relicense or make contributions.

## Contributing
- Fork, create a feature branch, and submit a pull request. If you add tests
	or CI, please include clear instructions in this README.

If you'd like, I can also add CI, a `LICENSE`, or example commands for training
and evaluating — tell me which you'd prefer.
