# CMakeLists.txt (engine)
# Add files
file(GLOB_RECURSE WILLOWVOXENGINE_SOURCES src/*.cpp)
# Define the library target
add_library(WillowVoxEngine STATIC ${WILLOWVOXENGINE_SOURCES})

# Include directories
target_include_directories(WillowVoxEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

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