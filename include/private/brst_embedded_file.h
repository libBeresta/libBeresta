#ifndef PRIVATE_BRST_EMBEDDED_FILE_H
#define PRIVATE_BRST_EMBEDDED_FILE_H

#include "brst_embedded_file.h"

BRST_EmbeddedFile
BRST_EmbeddedFile_New(
    BRST_MMgr mmgr,
    BRST_Xref xref,
    BRST_CSTR file
);

BRST_BOOL
BRST_EmbeddedFile_Validate(
    BRST_EmbeddedFile emfile
);

BRST_Dict
BRST_EmbeddedFile_Params(
    BRST_EmbeddedFile emfile
);

BRST_Dict
BRST_EmbeddedFile_FileStream(
    BRST_EmbeddedFile emfile
);

#endif /* PRIVATE_BRST_EMBEDDED_FILE_H */