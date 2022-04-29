### Ownership and License

The contributors are listed in CONTRIB.TXT. This project uses the GPL v3 license, see LICENSE.TXT.
This project uses the [C4.1 (Collective Code Construction Contract)](http://rfc.zeromq.org/spec:22) process for contributions.
To report an issue, use the [issues page](https://github.com/eez-open/eez-flow-template-sdl/issues) tracker.

## Build

#### Linux

```
sudo apt-get update
sudo apt-get install -y git libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev cmake build-essential libbsd-dev
git clone https://github.com/eez-open/eez-flow-template-sdl
mkdir -p eez-flow-template-sdl/build/linux
cd eez-flow-template-sdl/build/linux
cmake ../..
make
```

Start simulator with:

```
./eez-flow-template-sdl
```

#### Windows

Install [Visual Studio Community 2017](https://visualstudio.microsoft.com/downloads/) and [CMake](https://cmake.org/install/).

Use git to clone https://github.com/eez-open/eez-flow-template-sdl.

Execute `cmake.bat`.

Visual Studio solution is created in `\path\to\eez-flow-template-sdl\build\win32`.
