#ifndef BRST_DOC_SECURITY_H
#define BRST_DOC_SECURITY_H

/**

  \ingroup security
  \brief Sets a password for the document. If the password is set, document contents is encrypted.

  \copydoc dox_param_pdf
  \param owner_password Owner password of the document. The owner can change document permission. \c NULL, zero-length string and the same value as user password are not allowed.
  \param user_password User password of the document. The \c user_password may be set to \c NULL or zero-length string.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM
  - \ref BRST_ENCRYPT_INVALID_PASSWORD

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetPassword(
    BRST_Doc  pdf,
    BRST_CSTR owner_password,
    BRST_CSTR user_password
);

/**

  \ingroup security
  \brief Set the permission flags for the document.

  \copydoc dox_param_pdf
  \param permission \parblock One or more of the following values, combined together using binary \c OR:
  | Permission                | Description                                                                        |
  | ----------                | -----------                                                                        |
  | \ref BRST_ENABLE_READ     | User can read the document.                                                        |
  | \ref BRST_ENABLE_PRINT    | User can print the document.                                                       |
  | \ref BRST_ENABLE_EDIT_ALL | User can edit the contents of the document other than annotations and form fields. |
  | \ref BRST_ENABLE_COPY     | User can copy the text and the graphics of the document.                           | 
  | \ref BRST_ENABLE_EDIT     | User can add or modify the annotations and form fields of the document.            |
  \endparblock

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetPermission(
    BRST_Doc  pdf,
    BRST_UINT permission
);

/**

  \ingroup security
  \brief Set the encryption mode. As the side effect, ups the version of PDF to 1.4 when the mode is set to \ref BRST_ENCRYPT_R3.

  \copydoc dox_param_pdf
  \param mode \parblock One of the following values:
  | Mode                 | Description                                                                    |
  | ----                 | -----------                                                                    |
  | \ref BRST_ENCRYPT_R2 | Use "Revision 2" algorithm.<br/>\c key_len automatically set to 5 (40 bits).   |
  | \ref BRST_ENCRYPT_R3 | Use "Revision 3" algorithm.<br/>\c key_len can be 5 (40 bits) to 16 (128bits). |
  \endparblock

  \param key_len Specify byte length of encryption key. Only valid for \ref BRST_ENCRYPT_R3, length between 5 (40 bits) and 16 (128 bits) can be specified.

  \copydoc dox_return_ok

  \copydoc dox_error_codes

  - \ref BRST_INVALID_DOCUMENT
  - \ref BRST_INVALID_ENCRYPT_KEY_LEN
  - \ref BRST_FAILED_TO_ALLOC_MEM

*/
BRST_EXPORT(BRST_STATUS)
BRST_Doc_SetEncryptionMode(
    BRST_Doc           pdf,
    BRST_EncryptMode   mode,
    BRST_UINT          key_len
);
#endif /* BRST_DOC_SECURITY_H */