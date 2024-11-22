# CMakeLists.txt (root)
cmake_minimum_required(VERSION 3.15)
project(WillowVoxEngine
    LANGUAGES CXX C
    VERSION 0.1.0
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add engine and test projects
add_subdirectory(engine)
add_subdirectory(test)

# Copy assets folder to build folder
add_custom_target(copy_assets ALL
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/engine/assets
    ${CMAKE_BINARY_DIR}/bin/Debug/assets
    COMMENT "Copying assets"
)