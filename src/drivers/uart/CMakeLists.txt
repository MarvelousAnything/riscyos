set(UART_SOURCES uart.c)

add_library(uart_driver OBJECT ${UART_SOURCES})

target_include_directories(
  uart_driver PRIVATE ${CMAKE_SOURCE_DIR}/include
                      ${CMAKE_SOURCE_DIR}/include/drivers)
