# Copyright 2025 NXP
#
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.22.0)

include(${SdkRootDirPath}/cmake/extension/mcux.cmake)

project(lvgl_guider_bm LANGUAGES C CXX ASM PROJECT_BOARD_PORT_PATH ${board_root}/${board}/lvgl_examples/lvgl_guider_bm)

mcux_project_remove_source(
    BASE_PATH ${SdkRootDirPath}
    SOURCES examples/_boards/frdmmcxn947/board.c
            examples/_boards/frdmmcxn947/board.h
)

include(${SdkRootDirPath}/CMakeLists.txt)
# Includes del proyecto

mcux_add_include(INCLUDES
    include/
    generated/
    custom/
    linker/
)


mcux_add_source(
    SOURCES
        include/guider_customer_fonts.h
        include/lv_conf_ext.h
        include/lvgl_demo_utils.h
        include/RTE_Device.h
        include/pin_mux.h
        include/board.h
        include/__oledc_driver.h
)


mcux_convert_binary(BINARY ${APPLICATION_BINARY_DIR}/${MCUX_SDK_PROJECT_NAME}.bin)

# Fuentes principales
mcux_add_source(BASE_PATH ${CMAKE_CURRENT_LIST_DIR}
    SOURCES
        "src/__oledc_driver.c"
        "src/__oledc_hal.c"
        "src/joystick-2-click.c"
        "src/lvgl_demo_utils.c"
        "src/lvgl_guider_bm.c"
        "src/lvgl_support.c"
        "src/pin_mux.c"
        "src/board.c"
)

# Agregar LVGL 8.3.10
add_subdirectory(modules/lvgl)
target_link_libraries(${MCUX_SDK_PROJECT_NAME} PRIVATE lvgl)


file(GLOB CUSTOM_SOURCES RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/custom/*.c)
file(GLOB GENERATED_SOURCES RELATIVE ${CMAKE_CURRENT_LIST_DIR} ${CMAKE_CURRENT_LIST_DIR}/generated/*.c)

mcux_add_source(BASE_PATH ${CMAKE_CURRENT_LIST_DIR} SOURCES ${CUSTOM_SOURCES} ${GENERATED_SOURCES})


mcux_remove_armgcc_linker_script(
    BASE_PATH ${SdkRootDirPath}
    TARGETS debug release
    LINKER ${device_root}/${soc_portfolio}/${soc_series}/${device}/gcc/mcxn947_cm33_core0_flash.ld
)

mcux_add_armgcc_linker_script(
    TARGETS debug release
    LINKER linker/mcxn947_cm33_core0_flash_local.ld
)