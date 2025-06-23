#ifndef BRST_EMBEDDED_FILE_H
#define BRST_EMBEDDED_FILE_H

typedef enum _BRST_AFRelationship {
    BRST_AFRELATIONSHIP_SOURCE = 0,
    BRST_AFRELATIONSHIP_DATA,
    BRST_AFRELATIONSHIP_ALTERNATIVE,
    BRST_AFRELATIONSHIP_SUPPLEMENT,
    BRST_AFRELATIONSHIP_ENCRYPTEDPAYLOAD,
    BRST_AFRELATIONSHIP_FORMDATA,
    BRST_AFRELATIONSHIP_SCHEMA,
    BRST_AFRELATIONSHIP_UNSPECIFIED
} BRST_AFRelationship;

typedef BRST_Dict BRST_EmbeddedFile;

BRST_EXPORT(BRST_STATUS)
BRST_EmbeddedFile_SetName(
    BRST_EmbeddedFile emfile,
    BRST_CSTR         name
);

BRST_EXPORT(BRST_STATUS)
BRST_EmbeddedFile_SetDescription(
    BRST_EmbeddedFile emfile,
    BRST_CSTR         new_description
);

BRST_EXPORT(BRST_STATUS)
BRST_EmbeddedFile_SetSubtype(
    BRST_EmbeddedFile emfile,
    BRST_CSTR         subtype
);

BRST_EXPORT(BRST_STATUS)
BRST_EmbeddedFile_SetAFRelationship(
    BRST_EmbeddedFile   emfile,
    BRST_AFRelationship relationship
);

BRST_EXPORT(BRST_STATUS)
BRST_EmbeddedFile_SetSize(
    BRST_EmbeddedFile emfile,
    BRST_UINT64       size
);

BRST_EXPORT(BRST_STATUS)
BRST_EmbeddedFile_SetCreationDate(
    BRST_EmbeddedFile emfile,
    BRST_Date         creationDate
);

BRST_EXPORT(BRST_STATUS)
BRST_EmbeddedFile_SetLastModificationDate(
    BRST_EmbeddedFile emfile,
    BRST_Date         lastModificationDate
);

#endif /* BRST_EMBEDDED_FILE_H */