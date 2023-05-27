cmake_minimum_required(VERSION 3.11)
project(raygui C)

# Config options
option(BUILD_RAYGUI_EXAMPLES "Build the examples." OFF)

# Force building examples if building in the root as standalone.
if(CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR)
    set(BUILD_RAYGUI_EXAMPLES TRUE)
endif()

# Directory Variables
set(RAYGUI_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
set(RAYGUI_SRC ${RAYGUI_ROOT}/src)
set(RAYGUI_EXAMPLES ${RAYGUI_ROOT}/examples)

# raygui
add_library(raygui INTERFACE)
file(GLOB sources ${RAYGUI_SRC}/*.h)
set(RAYGUI_HEADERS ${sources})
install(FILES
    ${RAYGUI_HEADERS} DESTINATION include
)
target_include_directories(raygui INTERFACE ${RAYGUI_SRC})
