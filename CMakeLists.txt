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
set(PICO_BOARD pico CACHE STRING "Board type")

cmake_minimum_required(VERSION 3.12)

# Caminho do FreeRTOS Kernel
if (DEFINED ENV{FREERTOS_PATH})
    set(FREERTOS_PATH $ENV{FREERTOS_PATH})
else()
    set(FREERTOS_PATH ${CMAKE_CURRENT_LIST_DIR}/FreeRTOS)
endif()

message("FreeRTOS Kernel localizado em ${FREERTOS_PATH}")

# Importa o SDK
include(pico_sdk_import.cmake)

# Define o projeto
project(embarcatech-freertos-tarefa-1 C CXX ASM)
pico_sdk_init()

# Cria o executável com main.c
add_executable(embarcatech-freertos-tarefa-1
    main.c
)

# Inclui diretórios de cabeçalhos
target_include_directories(embarcatech-freertos-tarefa-1 PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${FREERTOS_PATH}/include
    ${FREERTOS_PATH}/portable
    ${FREERTOS_PATH}/portable/ThirdParty/GCC/RP2040/include
)



# Adiciona arquivos-fonte do kernel
target_sources(embarcatech-freertos-tarefa-1 PRIVATE
    ${FREERTOS_PATH}/tasks.c
    ${FREERTOS_PATH}/queue.c
    ${FREERTOS_PATH}/list.c
    ${FREERTOS_PATH}/timers.c
    ${FREERTOS_PATH}/event_groups.c
    ${FREERTOS_PATH}/stream_buffer.c
    ${FREERTOS_PATH}/croutine.c
    ${FREERTOS_PATH}/portable/ThirdParty/GCC/RP2040/port.c
    ${FREERTOS_PATH}/portable/MemMang/heap_4.c
)

# Liga com as bibliotecas necessárias do pico-sdk
target_link_libraries(embarcatech-freertos-tarefa-1
    pico_stdlib
    hardware_irq
    hardware_timer
    hardware_sync
    hardware_exception
    hardware_structs
)



# Gera arquivos .uf2 etc
pico_add_extra_outputs(embarcatech-freertos-tarefa-1)