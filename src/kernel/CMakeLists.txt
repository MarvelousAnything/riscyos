set(KERNEL_SOURCES
    main.c
    trap.c
    syscall.c
    timer.c
    device_manager.c
    logger.c
    mutex.c
    putchar.c)

add_library(kernel_core OBJECT ${KERNEL_SOURCES})

target_include_directories(kernel_core
                           PRIVATE ${CMAKE_SOURCE_DIR}/include/kernel)
