add_subdirectory(arch/riscv)
add_subdirectory(kernel)
add_subdirectory(lib)

if(ENABLE_UART_DRIVER)
  add_subdirectory(drivers/uart)
endif()

add_executable(kernel.elf "")

target_link_options(kernel.elf PRIVATE
  "-T${CMAKE_SOURCE_DIR}/src/arch/riscv/boot/linker.ld" "-Wl,-Map=kernel.map")

# Add all object files to kernel.elf
add_dependencies(kernel.elf arch_riscv kernel_core lib)
target_link_libraries(kernel.elf PRIVATE arch_riscv kernel_core lib)

if(ENABLE_UART_DRIVER)
  add_dependencies(kernel.elf uart_driver)
  target_link_libraries(kernel.elf PRIVATE uart_driver)
endif()
