# CMakeLists.txt (test)
# Define executable target
add_executable(WVTest 
    src/main.cpp
)

# Link the engine library
target_link_libraries(WVTest PRIVATE WillowVoxEngine)

# Include directories
target_include_directories(WVTest 
    PRIVATE 
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/engine/include
)

# Set output properties for the library
set_target_properties(WVTest PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)