# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
# Generated CMake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(TARGET_GROUP "test")

# Initialise pico_sdk from installed location
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()

set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if(EXISTS ${picoVscode})
    include(${picoVscode})
endif()

set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(base_project C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Decide source files based on TARGET_GROUP
if(TARGET_GROUP STREQUAL release)
    set(PROJECT_SOURCES
        base_project.c
    )
elseif(TARGET_GROUP STREQUAL test)
    include(CTest)
    set(PROJECT_SOURCES
        unity/unity.c
        temperature/temperature.c
        test/TestTemperature.c
    )
else()
    message(FATAL_ERROR "Unknown TARGET_GROUP: '${TARGET_GROUP}' (expected 'release' or 'test')")
endif()

# Add executable with selected sources
add_executable(base_project ${PROJECT_SOURCES})

# Basic project settings
pico_set_program_name(base_project "base_project")
pico_set_program_version(base_project "0.1")

# Enable stdio
pico_enable_stdio_uart(base_project 0)
pico_enable_stdio_usb(base_project 1)

# Standard library
target_link_libraries(base_project
    pico_stdlib
)

# Include project root
target_include_directories(base_project PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}
)

# Add extra outputs (UF2, bin, etc.)
pico_add_extra_outputs(base_project)