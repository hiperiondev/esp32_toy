file(
    GLOB_RECURSE
        SOURCES
            source/common/*.c
            source/compiler/*.c
            source/interpreter/*.c
            library/others/*.c
            library/libs/*.c
)

idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS
        include/common/
        include/compiler/
        include/interpreter/
        library/others/
        library/libs/
    REQUIRES
        hal_esp32
)