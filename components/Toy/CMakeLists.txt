file(
    GLOB_RECURSE
        SOURCES
            source/common/*.c
            source/compiler/*.c
            source/interpreter/*.c
            source/others/*.c
            library/repl/*.c
            library/source/*.c
)

idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS
        include/common/
        include/compiler/
        include/interpreter/
        include/others/
        library/repl/
        library/include/
    REQUIRES
        hal_esp32
)