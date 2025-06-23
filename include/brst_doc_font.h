#ifndef BRST_DOC_FONT_H
#define BRST_DOC_FONT_H

/**

  \ingroup font
  \brief Get requested font object handle.

  \copydoc dox_param_pdf
  \param font_name Valid font name.
  \param encoding_name Valid encoding name.

  \return Font object handle on success, otherwise returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_INVALID_FONT_NAME
  - \ref BRST_INVALID_ENCODING_NAME
  - \ref BRST_UNSUPPORTED_FONT_TYPE

  \see \ref fonts, \ref encodings
*/
BRST_EXPORT(BRST_Font)
BRST_Doc_Font(
    BRST_Doc  pdf,
    BRST_CSTR font_name,
    BRST_CSTR encoding_name
);

/**

  \ingroup font
  \brief Load Type1 font from external file and register it in the document object.

  \copydoc dox_param_pdf
  \param afm_filename Path of AFM file
  \param data_filename Path of PFA/PFB file. If \c NULL, glyph data of font file is not embedded into the PDF file


  \return Name of the font on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_FONT_EXISTS
  - \ref BRST_INVALID_AFM_HEADER
  - \ref BRST_INVALID_CHAR_MATRICS_DATA
  - \ref BRST_INVALID_N_DATA
  - \ref BRST_UNSUPPORTED_TYPE1_FONT

  \see \ref fonts

*/
BRST_EXPORT(BRST_CSTR)
BRST_Doc_Type1Font_LoadFromFile(
    BRST_Doc  pdf,
    BRST_CSTR afm_filename,
    BRST_CSTR data_filename
);

/**

  \ingroup font
  \brief Load TrueType font from external `.ttf` file and register it in the document object.

  \copydoc dox_param_pdf
  \param filename Path of TrueType font file (`.ttf`)
  \param embedding If this parameter is set to \ref BRST_TRUE, the glyph data of the font is included to PDF file, otherwise only the matrix data is included to PDF file.

  \return Name of the font on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_FONT_EXISTS
  - \ref BRST_INVALID_TTC_INDEX
  - \ref BRST_INVALID_TTC_FILE
  - \ref BRST_TTF_INVALID_CMAP
  - \ref BRST_TTF_INVALID_FOMAT
  - \ref BRST_TTF_MISSING_TABLE
  - \ref BRST_TTF_CANNOT_EMBEDDING_FONT

  \see \ref fonts

*/
BRST_EXPORT(BRST_CSTR)
BRST_Doc_TTFont_LoadFromFile(
    BRST_Doc  pdf,
    BRST_CSTR filename,
    BRST_BOOL embedding
);

/**

  \ingroup font
  \brief Load TrueType font from TrueType collection file `*.ttc` and register it in the document object.

  \copydoc dox_param_pdf
  \param filename Path of TrueType font file (`.ttc`)
  \param index Index of font in collection to be loaded.
  \param embedding If this parameter is set to \ref BRST_TRUE, the glyph data of the font is included to PDF file, otherwise only the matrix data is included to PDF file.

  \return Name of the font on success, otherwise, it returns \c NULL and calls error handler.

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_FONT_EXISTS
  - \ref BRST_INVALID_TTC_INDEX
  - \ref BRST_INVALID_TTC_FILE
  - \ref BRST_TTF_INVALID_CMAP
  - \ref BRST_TTF_INVALID_FOMAT
  - \ref BRST_TTF_MISSING_TABLE
  - \ref BRST_TTF_CANNOT_EMBEDDING_FONT
  - \ref BRST_INVALID_TTC_INDEX

  \see \ref fonts, \ref encodings

*/
BRST_EXPORT(BRST_CSTR)
BRST_Doc_TTFont_LoadFromFile2(
    BRST_Doc  pdf,
    BRST_CSTR filename,
    BRST_UINT index,
    BRST_BOOL embedding
);

BRST_EXPORT(BRST_CSTR)
BRST_Doc_TTFont_LoadFromMemory(
    BRST_Doc         pdf,
    const BRST_BYTE* buffer,
    BRST_UINT        size,
    BRST_BOOL        embedding
);

#endif /* BRST_DOC_FONT_H */