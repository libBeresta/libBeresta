set(
    LIBBRST_SRCS
        brst_annotation.c
        brst_base.c
        brst_destination.c
        brst_doc_annotation.c
        brst_doc_compression.c
        brst_doc_embedded_file.c
        brst_doc_encoder.c
        brst_doc_encoding_cns.c
        brst_doc_encoding_cnt.c
        brst_doc_encoding_jp.c
        brst_doc_encoding_kr.c
        brst_doc_encoding_utf.c
        brst_doc_font.c
        brst_doc_font_ttf.c
        brst_doc_font_type1.c
        brst_doc_fontdef_cns.c
        brst_doc_fontdef_cnt.c
        brst_doc_fontdef_jp.c
        brst_doc_fontdef_kr.c
        brst_doc_icc_profile.c
        brst_doc_image_jpeg.c
        brst_doc_image_png.c
        brst_doc_image_tiff.c
        brst_doc_info.c
        brst_doc_outline.c
        brst_doc_page.c
        brst_doc_page_xobject.c
        brst_doc_pdfa.c
        brst_doc_save.c
        brst_doc_security.c
        brst_doc_stream.c
        brst_doc_viewer.c
        brst_embedded_file.c
        brst_encoder.c
        brst_error.c
        brst_ext_gstate.c
        brst_font.c
        brst_geometry.c
        brst_image.c
        brst_outline.c
        brst_page.c
        brst_page.c
        brst_page_image.c
        brst_page_xobject.c
        brst_text.c
#[[
#]]
    )

set(
    LIBBRST_PRIVATE_SRCS
        private/brst_annotation.c
        private/brst_array.c
        private/brst_binary.c
        private/brst_boolean.c
        private/brst_catalog.c
        private/brst_destination.c
        private/brst_dict.c
        private/brst_direct.c
        private/brst_doc.c
        private/brst_doc_encoder.c
        private/brst_doc_encryption.c
        private/brst_doc_font.c
        private/brst_doc_fontdef.c
        private/brst_doc_info.c
        private/brst_doc_pages.c
        private/brst_embedded_file.c
        private/brst_encoder.c
        private/brst_encoder_basic.c
        private/brst_encoder_cmap.c
        private/brst_encoding_cns.c
        private/brst_encoding_cnt.c
        private/brst_encoding_jp.c
        private/brst_encoding_kr.c
        private/brst_encoding_utf.c
        private/brst_encrypt.c
        private/brst_encrypt_dict.c
        private/brst_error.c
        private/brst_ext_gstate.c
        private/brst_font.c
        private/brst_font_cid.c
        private/brst_font_ttf.c
        private/brst_font_type1.c
        private/brst_fontdef.c
        private/brst_fontdef_base14.c
        private/brst_fontdef_cid.c
        private/brst_fontdef_cns.c
        private/brst_fontdef_cnt.c
        private/brst_fontdef_jp.c
        private/brst_fontdef_kr.c
        private/brst_fontdef_ttf.c
        private/brst_fontdef_type1.c
        private/brst_gstate.c
        private/brst_image.c
        private/brst_image_ccitt.c
        private/brst_image_jpeg.c
        private/brst_image_png.c
        private/brst_image_raw.c
        private/brst_list.c
        private/brst_md5.c
        private/brst_mmgr.c
        private/brst_name.c
        private/brst_name_dict.c
        private/brst_name_tree.c
        private/brst_null.c
        private/brst_number.c
        private/brst_object.c
        private/brst_object_write.c
        private/brst_outline.c
        private/brst_page.c
        private/brst_page_label.c
        private/brst_pages.c
        private/brst_pdfa.c
        private/brst_proxy.c
        private/brst_real.c
        private/brst_shading.c
        private/brst_stream.c
        private/brst_string.c
        private/brst_text.c
        private/brst_unicode_glyph.c
        private/brst_utils.c
        private/brst_xref.c
    )

add_library(brst ${LIB_TYPE} ${LIBBRST_PRIVATE_SRCS} ${LIBBRST_SRCS})

set_target_properties(brst
    PROPERTIES
        SOVERSION ${BRST_MAJOR_VERSION}.${BRST_MINOR_VERSION}
        VERSION ${BRST_VERSION}
    )

if (PNG_FOUND)
    include_directories(${PNG_INCLUDE_DIRS})
    target_link_libraries(brst ${PNG_LIBRARIES})
endif()
if (ZLIB_FOUND)
    include_directories(${ZLIB_INCLUDE_DIRS})
    target_link_libraries (brst ${ZLIB_LIBRARIES})
endif()

# Math library
if(UNIX AND NOT APPLE)
    target_link_libraries(brst ${M_LIB})
endif()
