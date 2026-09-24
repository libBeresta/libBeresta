cmake_minimum_required(VERSION 3.10)

file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/include/brst_version.h BRST_VERSION_H_CONTENTS REGEX " BRST_(MAJOR|MINOR|BUGFIX)_VERSION ")
string(REGEX MATCH "MAJOR_VERSION [0-9]+"  BRST_MAJOR_VERSION  ${BRST_VERSION_H_CONTENTS})
string(REGEX MATCH "MINOR_VERSION [0-9]+"  BRST_MINOR_VERSION  ${BRST_VERSION_H_CONTENTS})
string(REGEX MATCH "BUGFIX_VERSION [0-9]+" BRST_BUGFIX_VERSION ${BRST_VERSION_H_CONTENTS})
string(REGEX MATCH "[0-9]+" BRST_MAJOR_VERSION  ${BRST_MAJOR_VERSION})
string(REGEX MATCH "[0-9]+" BRST_MINOR_VERSION  ${BRST_MINOR_VERSION})
string(REGEX MATCH "[0-9]+" BRST_BUGFIX_VERSION ${BRST_BUGFIX_VERSION})

set(BRST_VERSION ${BRST_MAJOR_VERSION}.${BRST_MINOR_VERSION}.${BRST_BUGFIX_VERSION})

project(libbrst
    VERSION ${BRST_VERSION}
        DESCRIPTION "libBeresta -- свободная, кросс-платформенная библиотека для создания PDF-файлов с открытым исходным кодом."
    LANGUAGES
        C
    )

include(GNUInstallDirs)

option(LIBBRST_SHARED_LIB "Построить динамическую библиотеку (.dll/.so) вместо статической (.lib/.a)" ON)
option(LIBBRST_EXAMPLES "Построить примеры" OFF)
option(LIBBRST_JSON_YAML "Перестроить JSON и YAML файлы для привязок" OFF)
option(LIBBRST_DEBUG "Включить отладку" OFF)
option(LIBBRST_DEBUG_TRACE "Включить трассировку" OFF)

option(LIBBRST_ASIAN_SUPPORT "Включить поддержку азиатских языков" ON)
option(LIBBRST_U3D_SUPPORT "PDF: Включить поддержку U3D" OFF)
option(LIBBRST_ANNOTATIONS_SUPPORT "PDF: Включить поддержку аннотаций" ON)

option(LIBBRST_MEM_DEBUG "Отладка выделения памяти" OFF)
option(LIBBRST_TESTS "Построить тесты" ON)

if (MSVC)
  # Имеет смысл когда-нибудь включить предупреждения и разобраться с ними
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /Wall /wd4820 /wd5045")
else()
  set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic -fPIC")
endif()

set(BRST_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include" CACHE INTERNAL "")
include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/)
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)

if (${LIBBRST_SHARED_LIB})
  set(LIB_TYPE SHARED)
else()
  set(LIB_TYPE STATIC)
endif()

# Проверить доступность zlib
find_package(ZLIB)

# Проверить доступность png
find_package(PNG)

# Найти библиотеку math (*nix)
find_library(M_LIB m)

# Поддержка кода, использующего PNG
set (LIBBRST_HAVE_LIBPNG ${PNG_FOUND})

# Поддержка zlib в коде
set (LIBBRST_HAVE_ZLIB ${ZLIB_FOUND})

configure_file(
  ${PROJECT_SOURCE_DIR}/config/brst_config.h.cmake
  ${PROJECT_BINARY_DIR}/include/brst_config.h
)

include_directories(${PROJECT_BINARY_DIR}/include)

# brst.pc file for pkg-config
set(BRST_PC_REQUIRES_PRIVATE "")
if (PNG_FOUND)
  list(APPEND BRST_PC_REQUIRES_PRIVATE "libpng")
endif()
if (ZLIB_FOUND)
  list(APPEND BRST_PC_REQUIRES_PRIVATE "zlib")
endif()
string(REPLACE ";" " " BRST_PC_REQUIRES_PRIVATE "${BRST_PC_REQUIRES_PRIVATE}")
if (M_LIB)
  set(BRST_PC_LIBS_PRIVATE "-lm")
else()
  set(BRST_PC_LIBS_PRIVATE "")
endif()

configure_file(
  ${PROJECT_SOURCE_DIR}/config/brst.pc.in
  ${PROJECT_BINARY_DIR}/brst.pc
  @ONLY
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    FILES_MATCHING
        PATTERN "*.h"
        PATTERN "private" EXCLUDE
)
install(FILES ${PROJECT_BINARY_DIR}/include/brst_config.h
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(FILES ${PROJECT_BINARY_DIR}/brst.pc
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)

add_subdirectory(src)
if(LIBBRST_EXAMPLES)
    add_subdirectory(demo)
endif(LIBBRST_EXAMPLES)

if(LIBBRST_TESTS)
    add_subdirectory(tests)
endif(LIBBRST_TESTS)

if(LIBBRST_JSON_YAML)
    add_subdirectory(gen)
endif(LIBBRST_JSON_YAML)


