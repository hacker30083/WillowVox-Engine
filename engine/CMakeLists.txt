# CMakeLists.txt (engine)
# Define the library target
add_library(WillowVoxEngine STATIC
    src/Application/Application.cpp
    src/Application/Window.cpp
    src/Core/Logger.cpp
    src/Input/Input.cpp
    src/Rendering/OpenGLGraphicsAPI.cpp
    src/Rendering/Shader.cpp
    src/Rendering/Texture.cpp
    src/Rendering/Camera.cpp
    src/World/Chunk.cpp
    src/World/World.cpp
    src/World/GameObject.cpp

    dependencies/include/glad/src/glad.c
)

# Include directories
target_include_directories(WillowVoxEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(WillowVoxEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/include)

# Link libraries
target_link_libraries(WillowVoxEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/lib/glfw3.lib)

# Set output properties for the library
set_target_properties(WillowVoxEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/WillowVoxEngine/Version.h.in
    ${CMAKE_CURRENT_SOURCE_DIR}/include/WillowVoxEngine/Version.h
)

# Add platform-specific preprocessor definitions
if(WIN32)
    target_compile_definitions(WillowVoxEngine PUBLIC PLATFORM_WINDOWS)
elseif(APPLE)
    target_compile_definitions(WillowVoxEngine PUBLIC PLATFORM_MACOS)
elseif(UNIX)
    target_compile_definitions(WillowVoxEngine PUBLIC PLATFORM_LINUX)
else()
    message(FATAL_ERROR "Unknown platform!")
endif()