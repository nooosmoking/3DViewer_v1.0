cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(3DViewer)
include_directories(${PROJECT_SOURCE_DIR})
SET(CMAKE_C_FLAGS "-fprofile-arcs -ftest-coverage -DSUPPORT_FILEFORMAT_BMP -DSUPPORT_FILEFORMAT_JPG")
# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# OpenGL
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL REQUIRED)

set(RAYLIB_VERSION 4.5.0)
add_subdirectory(libs/raylib-45)
add_subdirectory(libs/raygui-36)

# Our Project
file(GLOB SRC_FILES src/*.c)
file(GLOB SRC_FILES_TEST tests/*.c tests/*.h)

add_executable(${PROJECT_NAME}  ${SRC_FILES} main.c)
add_executable(test ${SRC_FILES} ${SRC_FILES_TEST})

target_link_libraries(${PROJECT_NAME} raylib raygui)
target_link_libraries(test raylib raygui check)

# Web Configurations
if (${PLATFORM} STREQUAL "Web")
    # Tell Emscripten to build an example.html file.
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".html")
endif()

# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
    target_link_libraries(test "-framework IOKit")
    target_link_libraries(test "-framework Cocoa")
    target_link_libraries(test "-framework OpenGL")
endif()