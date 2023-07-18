file(
    GLOB_RECURSE
        SOURCES
            Toy/common/source/*.c
            Toy/compiler/source/*.c
            Toy/interpreter/source/*.c
            Toy/library/others/*.c
            Toy/library/libs/*.c
)

idf_component_register(
    SRCS ${SOURCES}
    INCLUDE_DIRS
        Toy/common/include/
        Toy/compiler/include/
        Toy/interpreter/include/
        Toy/library/others/
        Toy/library/libs/
    REQUIRES
        hal_esp32
)

add_compile_definitions(_EXTERNAL_FS_HAL_="hal_fs.h")