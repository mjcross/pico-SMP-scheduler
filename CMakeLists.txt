cmake_minimum_required(VERSION 3.12)

# Name project
SET(ProjectName rp2040-freertos-template)

# Set any variables required for importing libraries
SET(FREERTOS_KERNEL_PATH /Users/martin/pico/freertos-pico/FreeRTOS-Kernel)

# Import those libraries
include(pico_sdk_import.cmake)
include(${FREERTOS_KERNEL_PATH}/portable/ThirdParty/GCC/RP2040/FreeRTOS_Kernel_import.cmake)

# Define project
project(${ProjectName})

# Initialize the Raspberry Pi Pico SDK
pico_sdk_init()

# Add subdirectories
add_subdirectory(src)
