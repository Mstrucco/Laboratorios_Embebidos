# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

file(MAKE_DIRECTORY
  "/home/matit/esp/idf/esp-idf/components/bootloader/subproject"
  "/home/matit/esp/projects/Ejercicio_3/build/bootloader"
  "/home/matit/esp/projects/Ejercicio_3/build/bootloader-prefix"
  "/home/matit/esp/projects/Ejercicio_3/build/bootloader-prefix/tmp"
  "/home/matit/esp/projects/Ejercicio_3/build/bootloader-prefix/src/bootloader-stamp"
  "/home/matit/esp/projects/Ejercicio_3/build/bootloader-prefix/src"
  "/home/matit/esp/projects/Ejercicio_3/build/bootloader-prefix/src/bootloader-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/matit/esp/projects/Ejercicio_3/build/bootloader-prefix/src/bootloader-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/matit/esp/projects/Ejercicio_3/build/bootloader-prefix/src/bootloader-stamp${cfgdir}") # cfgdir has leading slash
endif()
