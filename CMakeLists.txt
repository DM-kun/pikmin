cmake_minimum_required(VERSION 3.25)

set(SPROUT_VERSION "0.1.0")
project(sprout LANGUAGES C CXX VERSION ${SPROUT_VERSION})

set(GAME_COMPILE_DEFS TARGET_PC BUGFIX VERSION_GPIP01)

# Add Aurora as a subdirectory
add_subdirectory(extern/aurora EXCLUDE_FROM_ALL)

set(AURORA_ENABLE_GX ON CACHE BOOL "Enable GX implementation and WebGPU renderer" FORCE)
set(AURORA_ENABLE_DVD ON CACHE BOOL "Enable DVD implementation backed by nod" FORCE)
set(AURORA_ENABLE_CARD ON CACHE BOOL "Enable CARD implementation based on kabufuda" FORCE)
set(AURORA_ENABLE_RMLUI ON CACHE BOOL "Enable HTML/CSS based UI library" FORCE)
set(AURORA_CACHE_USE_ZSTD ON CACHE BOOL "Compress WebGPU cache entries with zstd" FORCE)

# Add Game files
include(cmake/files.cmake)
set(GAME_BASE_FILES
    ${SYSTEM_FILES}
    ${JAUDIO_FILES}
    ${DOLPIK_FILES}
#    ${SPROUT_FILES}
)

# Create your executable
add_executable(sprout src/sprout/main.cpp ${GAME_BASE_FILES})

set(GAME_INCLUDE_DIRS
    include
    src
    extern/aurora/include
    extern
)

# Link against Aurora components
target_compile_definitions(sprout PRIVATE ${GAME_COMPILE_DEFS})
target_include_directories(sprout PRIVATE ${GAME_INCLUDE_DIRS})
target_link_libraries(sprout PRIVATE 
    aurora::main
    aurora::card
    aurora::core
    aurora::dvd
    aurora::gd
    aurora::gx
    aurora::mtx
    aurora::os
    aurora::pad
    aurora::si
    aurora::vi
)
