# WillowVox Engine
A voxel world engine

## Building

### Building with CMake
In the project root directory:
Create CMake files:
```sh
mkdir -p build
cd build
cmake ..
```
After that you can build the project using:
```sh
cmake --build ./build
```
Run the build command in the project root directory.

The final executable can be found at `(project root)/build/bin`

#### Note for building with CMake
If you're running from a command line, make sure to run
the executable in the same directory as it is located
to ensure all resources are loaded properly.