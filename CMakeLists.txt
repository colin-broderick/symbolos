cmake_minimum_required(VERSION 3.31)
project(symbol CXX ASM)

set(CMAKE_SYSTEM_NAME SymbolOS)
set(CMAKE_SYSTEM_PROCESSOR i686)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_C_COMPILER i686-elf-gcc)
set(CMAKE_ASM_COMPILER i686-elf-as)
set(CMAKE_CXX_COMPILER i686-elf-g++)
set(CMAKE_LINKER i686-elf-g++)

set(sources
    src/boot.s
    src/kernel.cpp
    src/symbollib.cpp
    src/terminal.cpp
    src/vga.cpp)

add_executable(symbol.bin ${sources})

target_include_directories(symbol.bin PRIVATE include)

target_compile_options(symbol.bin PRIVATE
    $<$<COMPILE_LANGUAGE:CXX>:
        -ffreestanding
        -Wall
        -Wextra
        -O2
        -Werror
        -fno-exceptions
        -fno-rtti
    >)

target_link_options(symbol.bin PRIVATE
    -T ${CMAKE_CURRENT_SOURCE_DIR}/linker_scripts/linker.ld
    -ffreestanding
    -O2
    -nostdlib
    -lgcc)

# Build the artefacts into an ISO which can be installed or run in an emulator.
add_custom_target(iso
    COMMAND mkdir -p isodir/boot/grub
    COMMAND cp ${CMAKE_CURRENT_BINARY_DIR}/symbol.bin isodir/boot/symbol.bin
    COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/configuration_data/grub.cfg isodir/boot/grub/grub.cfg
    COMMAND grub-mkrescue -o symbol.iso isodir
    DEPENDS ${PROJECT_NAME}.bin)
