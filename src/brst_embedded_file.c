#include "brst_external.h"
#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "brst_encoder.h"
#include "brst_error.h"
#include "brst_consts.h"
#include "brst_array.h"
#include "private/brst_string.h"
#include "brst_embedded_file.h"
#include "private/brst_embedded_file.h"
#include "private/brst_utils.h"
#include "brst_base.h"
#include "brst_doc_info.h"
#include "private/brst_info.h"

BRST_EXPORT(BRST_STATUS)
BRST_EmbeddedFile_SetName(BRST_EmbeddedFile emfile,
    BRST_CSTR new_name)
{
    BRST_Dict filestream;
    BRST_String name; /* the name of the file: /F (name) */
    BRST_String ufname; /* the unicode name of the file: /UF (name) */
    BRST_STATUS status;

    filestream = BRST_EmbeddedFile_FileStream(emfile);
    if (!filestream)
        return BRST_INVALID_OBJECT;

    name = BRST_String_New(emfile->mmgr, new_name, NULL);
    if (!name)
        return BRST_FAILED_TO_ALLOC_MEM;

    ufname = BRST_String_New(emfile->mmgr, new_name, NULL);
    if (!ufname)
        return BRST_FAILED_TO_ALLOC_MEM;

    status = BRST_Dict_Add(emfile, "F", name);
    if (status == BRST_OK)
        status = BRST_Dict_Add(emfile, "UF", ufname);

    return status;
}

BRST_EXPORT(BRST_STATUS)
BRST_EmbeddedFile_SetDescription(BRST_EmbeddedFile emfile,
    BRST_CSTR new_description)
{
    BRST_Dict filestream;
    BRST_String description; /* the name of the file: /F (name) */

    filestream = BRST_EmbeddedFile_FileStream(emfile);
    if (!filestream)
        return BRST_INVALID_OBJECT;

    description = BRST_String_New(emfile->mmgr, new_description, NULL);
    if (!description)
        return BRST_FAILED_TO_ALLOC_MEM;

    return BRST_Dict_Add(emfile, "Desc", description);
}

BRST_EXPORT(BRST_STATUS)
BRST_EmbeddedFile_SetSubtype(BRST_EmbeddedFile emfile,
    BRST_CSTR subtype)
{
    BRST_Dict filestream;

    filestream = BRST_EmbeddedFile_FileStream(emfile);
    if (!filestream)
        return BRST_INVALID_OBJECT;

    return BRST_Dict_AddName(filestream, "Subtype", subtype);
}

BRST_EXPORT(BRST_STATUS)
BRST_EmbeddedFile_SetAFRelationship(BRST_EmbeddedFile emfile,
    BRST_AFRelationship relationship)
{
    // This array has to be kept coherent with BRST_AFRelationship enum.
    static const char* relationships[] = {
        "Source",
        "Data",
        "Alternative",
        "Supplement",
        "EncryptedPayload",
        "FormData",
        "Schema",
        "Unspecified"
    };

    if (relationship < 0 || relationship > BRST_AFRELATIONSHIP_UNSPECIFIED) {
        return BRST_INVALID_PARAMETER;
    }
    return BRST_Dict_AddName(emfile, "AFRelationship", relationships[relationship]);
}

BRST_EXPORT(BRST_STATUS)
BRST_EmbeddedFile_SetSize(BRST_EmbeddedFile emfile,
    BRST_UINT64 size)
{
    BRST_Dict params;

    params = BRST_EmbeddedFile_Params(emfile);
    if (!params)
        return BRST_Error_Code(emfile->error);

    return BRST_Dict_AddNumber(params, "Size", (BRST_INT32)size);
}

BRST_EXPORT(BRST_STATUS)
BRST_EmbeddedFile_SetCreationDate(BRST_EmbeddedFile emfile,
    BRST_Date creationDate)
{
    BRST_Dict params;

    params = BRST_EmbeddedFile_Params(emfile);
    if (!params)
        return BRST_Error_Code(emfile->error);

    return BRST_Info_SetInfoDateAttr(params, BRST_INFO_CREATION_DATE, creationDate);
}

BRST_EXPORT(BRST_STATUS)
BRST_EmbeddedFile_SetLastModificationDate(BRST_EmbeddedFile emfile,
    BRST_Date lastModificationDate)
{
    BRST_Dict params;

    params = BRST_EmbeddedFile_Params(emfile);
    if (!params)
        return BRST_Error_Code(emfile->error);

    return BRST_Info_SetInfoDateAttr(params, BRST_INFO_MOD_DATE, lastModificationDate);
}
