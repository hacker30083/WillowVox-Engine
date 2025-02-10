# CMakeLists.txt (test)
project(WVTest)

# Define executable target
add_executable(WVTest 
    src/main.cpp
)

# Link the engine library
target_link_libraries(WVTest PRIVATE WillowVoxEngine)
target_link_libraries(WVTest PUBLIC imgui)

# Include directories
target_include_directories(WVTest PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/engine/include
    ${CMAKE_SOURCE_DIR}/external
)

# Set output properties for the library
set_target_properties(WVTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)