# WillowVox Engine

![GitHub Actions Workflow Status](https://img.shields.io/github/actions/workflow/status/EvanatorM/WillowVox-Engine/multi-platform-build-test.yml) ![Static Badge](https://img.shields.io/badge/Version-_V0.2-green?style=flat)


A voxel world engine

**Read the docs at https://WillowVox.com/docs/api**

## Building

### Installing dependencies

If you are on linux you need the following packages
```sh
sudo apt install libwayland-dev libxkbcommon-dev xorg-dev
```

### Build GLFW
From WillowVox directory run the following:
```sh
git clone https://github.com/glfw/glfw
cd glfw
mkdir build
cd build
cmake ..
cmake --build . --config *Build type here (Release or Debug)*
```
On linux:
```sh
cp ./src/libglfw3.a ../../external/
```
On Windows:
```sh
cp ./src/*Your Build type*/glfw3.lib ../../external/
```

And if the extra directory bothers you get rid of it with (On Windows remove the "-rf"):
```sh
cd ../../
rm -rf glfw
```
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
cmake --build ..
```
Run the build command in the project root directory.

The final executable can be found at `(project root)/build/bin/(build type)`

#### Note for building with CMake
If you're running from a command line, make sure to run
the executable in the same directory as it is located
to ensure all resources are loaded properly.

## Contributing
If you would like to contribute to WillowVox Engine, you can do so in a couple of ways:
1. If you notice any bugs or something that can be optimized, you can do that
2. If you want to add new features, you can look at the Projects tab of the repository. In there are projects for upcoming releases. In the projects, there is a Status Board tab. You can add anything in the ready status. You can also work on tasks in the in progress and in review status.
3. If you have ideas or thoughts about the engine, you can check out the Discussions tab of the repository or the [Discord server](https://discord.gg/ZZTUgsmy75)

I will flesh out the contributing guidelines soon. I may not accept your changes if they go against the vision of the engine, but I will always discuss what changes I don't want to commit and why, and we can work together to make the best changes possible for the engine.
