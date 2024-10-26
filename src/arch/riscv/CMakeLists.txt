set(ARCH_RISCV_SOURCES boot/start.S traps/trap.S)

add_library(arch_riscv OBJECT ${ARCH_RISCV_SOURCES})

set_source_files_properties(${ARCH_RISCV_SOURCES} PROPERTIES LANGUAGE ASM)

target_include_directories(arch_riscv
                           PRIVATE ${CMAKE_SOURCE_DIR}/include/arch/riscv)
