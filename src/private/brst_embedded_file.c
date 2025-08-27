#include "brst_types.h"
#include "brst_mmgr.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_dict.h"
#include "private/brst_string.h"
#include "brst_xref.h"
#include "private/brst_xref.h"
#include "brst_embedded_file.h"
#include "private/brst_embedded_file.h"
#include "brst_date.h"

#include "brst_consts.h"

BRST_EmbeddedFile
BRST_EmbeddedFile_New(
    BRST_MMgr mmgr,
    BRST_Xref xref,
    const char* file)
{
    BRST_STATUS ret = BRST_OK;
    BRST_Dict ef; /* the dictionary for the embedded file: /Type /EF */
    BRST_String name; /* the name of the file: /F (name) */
    BRST_String ufname; /* the unicode name of the file: /UF (name) */
    BRST_Dict eff; /* ef has an /EF <<blah>> key - this is it */
    BRST_Dict filestream; /* the stream that /EF <</F _ _ R>> refers to */
    BRST_Stream stream;

    ef = BRST_Dict_New(mmgr);
    if (!ef)
        return NULL;
    if (BRST_Xref_Add(xref, ef) != BRST_OK)
        return NULL;

    filestream = BRST_Dict_New_Stream_Init(mmgr, xref);
    if (!filestream)
        return NULL;
    stream = BRST_FileReader_New(mmgr, file);
    if (!stream)
        return NULL;
    BRST_Stream_Free(filestream->stream);
    filestream->stream = stream;

    // TODO Должно ли настраиваться сжатие?
    filestream->filter = BRST_STREAM_FILTER_FLATE_DECODE;

    eff = BRST_Dict_New(mmgr);
    if (!eff)
        return NULL;

    name = BRST_String_New(mmgr, file, NULL);
    if (!name)
        return NULL;

    ufname = BRST_String_New(mmgr, file, NULL);
    if (!ufname)
        return NULL;

    ret += BRST_Dict_AddName(ef, "Type", "Filespec");
    ret += BRST_Dict_Add(ef, "F", name);
    ret += BRST_Dict_Add(ef, "UF", ufname);
    ret += BRST_Dict_Add(ef, "EF", eff);
    ret += BRST_Dict_Add(eff, "F", filestream);
    ret += BRST_Dict_AddName(filestream, "Type", "EmbeddedFile");

    if (ret != BRST_OK)
        return NULL;

    return ef;
}

BRST_BOOL
BRST_EmbeddedFile_Validate(BRST_EmbeddedFile emfile)
{
    BRST_UNUSED(emfile);
    return BRST_TRUE;
}

BRST_Dict
BRST_EmbeddedFile_FileStream(BRST_EmbeddedFile emfile)
{
    BRST_Dict ef;

    ef = BRST_Dict_Item(emfile, "EF", BRST_OCLASS_DICT);
    if (!ef)
        return NULL;

    return BRST_Dict_Item(ef, "F", BRST_OCLASS_DICT);
}

BRST_Dict
BRST_EmbeddedFile_Params(BRST_EmbeddedFile emfile)
{
    BRST_Dict filestream;
    BRST_Dict params;

    filestream = BRST_EmbeddedFile_FileStream(emfile);
    if (!filestream)
        return NULL;

    params = BRST_Dict_Item(filestream, "Params", BRST_OCLASS_DICT);
    if (!params) {
        params = BRST_Dict_New(emfile->mmgr);
        if (!params || BRST_Dict_Add(filestream, "Params", params) != BRST_OK)
            return NULL;
    }
    return params;
}
