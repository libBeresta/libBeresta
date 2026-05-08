set(
  gen_data_names
    annotation
    array
    asian
    base
    consts
    date
    destination
    dict
    doc
    doc_compression
    doc_embedded_file
    doc_encoder
    doc_encoding_utf
    doc_ext_gstate
    doc_font
    doc_image_jpeg
    doc_image_png
    doc_image_tiff
    doc_info
    doc_matrix
    doc_page
    doc_page_pattern
    doc_pattern
    doc_pdfa
    doc_save
    doc_security
    doc_viewer
    doc_xobject
    encrypt
    error
    exdata
    ext_gstate
    font
    fontdef
    geometry
    geometry_defines
    javascript
    main
    matrix
    mmgr
    page
    page_routines
    page_sizes
    page_xobject
    pattern
    stream
    stream_geometry
    stream_text
    structs
    text
    text_defines
    types
    unicode_glyph
    xobject
    xref
)

set(gen_data_names_fullpath)
set(gen_data_names_fullpath_json)
set(gen_data_names_fullpath_yaml)

foreach(DATA ${gen_data_names})
  list(APPEND gen_data_names_fullpath ${CMAKE_SOURCE_DIR}/gen/data/${DATA}.lsp)
  list(APPEND gen_data_names_fullpath_json ${CMAKE_SOURCE_DIR}/gen/json/${DATA}.json)
  list(APPEND gen_data_names_fullpath_yaml ${CMAKE_SOURCE_DIR}/gen/yaml/${DATA}.yaml)
endforeach()
