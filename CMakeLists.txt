cmake_minimum_required(VERSION 3.10)

file(STRINGS ${CMAKE_CURRENT_SOURCE_DIR}/include/brst_version.h BRST_VERSION_H_CONTENTS REGEX " BRST_(MAJOR|MINOR|BUGFIX)_VERSION ")
string(REGEX MATCH "MAJOR_VERSION [0-9]+"  BRST_MAJOR_VERSION  ${BRST_VERSION_H_CONTENTS})
string(REGEX MATCH "MINOR_VERSION [0-9]+"  BRST_MINOR_VERSION  ${BRST_VERSION_H_CONTENTS})
string(REGEX MATCH "BUGFIX_VERSION [0-9]+" BRST_BUGFIX_VERSION ${BRST_VERSION_H_CONTENTS})
string(REGEX MATCH "[0-9]+" BRST_MAJOR_VERSION  ${BRST_MAJOR_VERSION})
string(REGEX MATCH "[0-9]+" BRST_MINOR_VERSION  ${BRST_MINOR_VERSION})
string(REGEX MATCH "[0-9]+" BRST_BUGFIX_VERSION ${BRST_BUGFIX_VERSION})

set(BRST_VERSION ${BRST_MAJOR_VERSION}.${BRST_MINOR_VERSION}.${BRST_BUGFIX_VERSION})

project(libharu
    VERSION ${BRST_VERSION}
        DESCRIPTION "libBeresto -- свободная, кросс-платформенная библиотека для создания PDF-файлов с открытым исходным кодом."
    LANGUAGES
        C
    )

include(GNUInstallDirs)

option(LIBBRST_SHARED_LIB "Построить динамическую библиотеку (.dll/.so) вместо статической (.lib/.a)" ON)
option(LIBBRST_EXAMPLES "Построить примеры" OFF)
option(LIBBRST_DEBUG "Включить отладку" OFF)
option(LIBBRST_DEBUG_TRACE "Включить трассировку" OFF)

option(LIBBRST_ASIAN_SUPPORT "Включить поддержку азиатских языков" ON)
option(LIBBRST_U3D_SUPPORT "PDF: Включить поддержку U3D" OFF)
option(LIBBRST_ANNOTATIONS_SUPPORT "PDF: Включить поддержку аннотаций" ON)

option(LIBBRST_MEM_DEBUG "Отладка выделения памяти" OFF)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -pedantic")

set(BRST_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include" CACHE INTERNAL "")
include_directories(${PROJECT_SOURCE_DIR}/include)
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

add_subdirectory(src)
if(LIBBRST_EXAMPLES)
    add_subdirectory(demo)
endif(LIBBRST_EXAMPLES)

set(
  haru_HDRS
    include/brst_annotation.h
    include/brst_array.h
    include/brst_asian.h
    include/brst_base.h
    include/brst_conf.h
    include/brst_consts.h
    include/brst_consts_.h
    include/brst_defines.h
    include/brst_destination.h
    include/brst_doc.h
    include/brst_doc_annotation.h
    include/brst_doc_compression.h
    include/brst_doc_encoder.h
    include/brst_doc_encoding_cns.h
    include/brst_doc_encoding_cnt.h
    include/brst_doc_encoding_jp.h
    include/brst_doc_encoding_kr.h
    include/brst_doc_ext_gstate.h
    include/brst_doc_font.h
    include/brst_doc_icc_profile.h
    include/brst_doc_image_jpeg.h
    include/brst_doc_image_png.h
    include/brst_doc_image_tiff.h
    include/brst_doc_info.h
    include/brst_doc_page_xobject.h
    include/brst_doc_save.h
    include/brst_doc_security.h
    include/brst_doc_stream.h
    include/brst_doc_viewer.h
    include/brst_embedded.h
    include/brst_encoding.h
    include/brst_encrypt.h
    include/brst_error.h
    include/brst_export.h
    include/brst_external.h
    include/brst_font.h
    include/brst_fontdef.h
    include/brst_geometry.h
    include/brst_image.h
    include/brst_mmgr.h
    include/brst_outline.h
    include/brst_page.h
    include/brst_page_sizes.h
    include/brst_page_sizes_iso_216.h
    include/brst_page_xobject.h
    include/brst_pdfa.h
    include/brst_shading.h
    include/brst_stream.h
    include/brst_text.h
    include/brst_types.h
    include/brst_stream_geometry.h
    include/brst_u3d.h
    include/brst_version.h
    ${PROJECT_BINARY_DIR}/include/brst_config.h
)

set(
    haru_PRIVATE_HDRS
        include/private/brst_annotation.h
        include/private/brst_array.h
        include/private/brst_binary.h
        include/private/brst_boolean.h
        include/private/brst_catalog.h
        include/private/brst_destination.h
        include/private/brst_dict.h
        include/private/brst_direct.h
        include/private/brst_doc.h
        include/private/brst_embedded.h
        include/private/brst_encoder.h
        include/private/brst_encoder_basic.h
        include/private/brst_encoder_cmap.h
        include/private/brst_encrypt.h
        include/private/brst_encrypt_dict.h
        include/private/brst_error.h
        include/private/brst_ext_gstate.h
        include/private/brst_font.h
        include/private/brst_fontdef.h
        include/private/brst_fontdef_base14.h
        include/private/brst_fontdef_cid.h
        include/private/brst_fontdef_ttf.h
        include/private/brst_fontdef_type1.h
        include/private/brst_geometry.h
        include/private/brst_gstate.h
        include/private/brst_image.h
        include/private/brst_image_jpeg.h
        include/private/brst_info.h
        include/private/brst_list.h
        include/private/brst_md5.h
        include/private/brst_mmgr.h
        include/private/brst_name.h
        include/private/brst_name_dict.h
        include/private/brst_name_tree.h
        include/private/brst_null.h
        include/private/brst_number.h
        include/private/brst_objects.h
        include/private/brst_outline.h
        include/private/brst_page.h
        include/private/brst_page_label.h
        include/private/brst_pages.h
        include/private/brst_pdfa.h
        include/private/brst_proxy.h
        include/private/brst_real.h
        include/private/brst_shading.h
        include/private/brst_streams.h
        include/private/brst_string.h
        include/private/brst_utils.h
        include/private/brst_xref.h
    )
