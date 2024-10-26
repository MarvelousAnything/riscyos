cmake_minimum_required(VERSION 3.30)
project(
  riscyos
  VERSION 0.1.0
  LANGUAGES C ASM)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(ENABLE_UART_DRIVER "Enable UART driver" ON)
option(ENABLE_VIDEO_DRIVER "Enable Video driver" OFF)
option(ENABLE_DEBUG "Enable debug mode" OFF)

set(ARCH "riscv64")
set(ABI "lp64")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
set(CMAKE_C_FLAGS_DEBUG "-O0 -g3")
set(CMAKE_C_FLAGS_RELEASE "-O0")

set(CMAKE_TOOLCHAIN_FILE
    "${CMAKE_SOURCE_DIR}/cmake/riscv64-unknown-elf-toolchain.cmake")

configure_file(${CMAKE_SOURCE_DIR}/include/config.h.in
               ${CMAKE_BINARY_DIR}/include/config.h)

include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_BINARY_DIR}/include)

add_subdirectory(src)

add_custom_target(
  run
  COMMAND qemu-system-riscv64 -nographic -bios none -machine virt -kernel src/kernel.elf
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  DEPENDS kernel.elf
  COMMENT "Running kernel in QEMU")

add_custom_target(
  debug
  COMMAND qemu-system-riscv64 -nographic -bios none -machine virt -kernel src/kernel.elf -S -s
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  DEPENDS kernel.elf
  COMMENT "Debugging kernel with GDB")
