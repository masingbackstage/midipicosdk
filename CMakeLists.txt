# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NEVER EDIT THE NEXT LINES for Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.0.0)
set(toolchainVersion 13_2_Rel1)
set(picotoolVersion 2.0.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(midick C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

#=====================================================================================


# Add executable. Default name is the project name, version 0.1

add_executable(midick src/midick.cpp 
               include/led.h src/led.cpp
               include/button.h src/button.cpp
               src/tusb_config.h
               src/usb_descriptors.c
               )

pico_set_program_name(midick "midick")
pico_set_program_version(midick "0.1")


# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(midick 0)
pico_enable_stdio_usb(midick 1)  # Zmienione na 1, aby włączyć USB


target_sources(midick PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/src/midick.cpp
        ${CMAKE_CURRENT_LIST_DIR}/src/usb_descriptors.c
        )

# Add the standard library to the build
target_link_libraries(
        midick
        pico_stdlib
        pico_unique_id
        tinyusb_device 
        tinyusb_board
        )

# Add the standard include files to the build
target_include_directories(midick PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${CMAKE_CURRENT_LIST_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}/.. # for our common lwipopts or any other standard includes, if required
        ${PICO_SDK_PATH}/lib/tinyusb/src 
        )

pico_add_extra_outputs(midick)
