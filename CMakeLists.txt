# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(APP_NAME "mdac_adc2")
set(BOARD_NAME "rp2040" CACHE STRING "Target board name")

# user configurations
set (PICODAC_I2S_DATA_PIN 22 CACHE STRING "I2S Data Pin")
set (PICODAC_I2S_BASE_CLOCK_PIN 20 CACHE STRING "I2S Base Clock Pin. LRCLK is BASE + 1")
set (PICODAC_VENDOR_ID 0xcafe CACHE STRING "USB Vendor ID")
set (PICODAC_PRODUCT_ID 0xbabe CACHE STRING "USB Product ID")





if(BOARD_NAME STREQUAL "rp2040")

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
# NOTE: VS Code Pico Extension relies on naive line-based parsing.
#       These lines must remain at top-level indentation (no leading spaces),
#       even if wrapped in an if(). Do not indent or reformat them.
if(WIN32)
set(USERHOME $ENV{USERPROFILE})
else()
set(USERHOME $ENV{HOME})
endif()
set(PICO_BOARD pico CACHE STRING "Board type")
set(sdkVersion 2.2.0)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.2.0)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
include(${picoVscode})
endif()
# ====================================================================================

    # pico-sdk requirement: include the SDK import before project()
    include(pico_sdk_import.cmake)

    # pico-sdk requirement: project() must come AFTER the include above,
    # and BEFORE pico_sdk_init() / add_subdirectory().
    project(mdac_adc2 C CXX ASM)

    # pico-sdk requirement: initialize the SDK AFTER project(),
    # and BEFORE adding any subdirectories/targets.
    pico_sdk_init()

    add_executable(mdac_adc2
        main.c
        audio_device.c
        blink.c
        i2s.c
        ringbuffer.c
        usb.c
        usb_audio.c
        usb_hid.c
    )
    # Add the standard library to the build
    target_link_libraries(mdac_adc2
        hardware_dma
        hardware_pio
        pico_stdlib
    )

    target_compile_definitions(mdac_adc2 PRIVATE
        PICODAC_I2S_DATA_PIN=${PICODAC_I2S_DATA_PIN}
        PICODAC_I2S_BASE_CLOCK_PIN=${PICODAC_I2S_BASE_CLOCK_PIN}
        PICO_PLL_VCO_MAX_FREQ_HZ=2304000000
        HID_ENABLE=1
        VENDOR_ID=${PICODAC_VENDOR_ID}
        PRODUCT_ID=${PICODAC_PRODUCT_ID}
    )

    # Add the standard include files to the build
    target_include_directories(mdac_adc2
    PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
    )

    pico_generate_pio_header(mdac_adc2
        ${CMAKE_CURRENT_LIST_DIR}/blink.pio
        ${CMAKE_CURRENT_LIST_DIR}/i2s.pio
    )

    pico_set_program_name(mdac_adc2 "mdac_adc2")
    pico_set_program_version(mdac_adc2 "0.1")

    # pico_set_binary_type(mdac_adc2 no_flash)

    # Modify the below lines to enable/disable output over UART/USB
    pico_enable_stdio_uart(mdac_adc2 1)
    pico_enable_stdio_usb(mdac_adc2 0)

    pico_add_extra_outputs(mdac_adc2)
    
endif()

# add_subdirectory(musb)
# target_link_libraries(mdac_adc2 musb)
