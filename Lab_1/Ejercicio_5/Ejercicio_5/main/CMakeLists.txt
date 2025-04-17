idf_component_register(SRCS "Ejercicio_5.c"
                    INCLUDE_DIRS "."
                    REQUIRES esp-dsp littlefs)
littlefs_create_partition_image(storage ../partition FLASH_IN_PROJECT)