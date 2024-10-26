set(LIB_SOURCES string.c printf.c)

add_library(lib OBJECT ${LIB_SOURCES})

add_definitions(-DPRINTF_DISABLE_SUPPORT_FLOAT)

target_include_directories(lib PRIVATE ${CMAKE_SOURCE_DIR}/include/lib)
