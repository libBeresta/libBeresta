#include "brst_types.h"
#include "brst_encrypt.h"
#include "brst_encoder.h"
#include "brst_stream.h"
#include "brst_mmgr.h"
#include "brst_dict.h"
#include "brst_xref.h"
#include "private/brst_xref.h"
#include "private/brst_name_dict.h"
#include "brst_consts.h"
#include "brst_error.h"
#include "private/brst_utils.h"

/* PDF 7.7.4 Name Dictionary */
static const char* const BRST_NAMEDICT_KEYS[] = {
    // TODO расставить ifdef
    "Dests", // Версия 1.2
    "AP", // Версия 1.3
    "JavaScript", // Версия 1.3
    "Pages", // Версия 1.3
    "Templates", // Версия 1.3
    "IDS", // Версия 1.3
    "URLS", // Версия 1.3
    "EmbeddedFiles", // Версия 1.4
    "AlternatePresentations", // Версия 1.4
    "Renditions", // Версия 1.5
    ""
};

BRST_NameDict
BRST_NameDict_New(BRST_MMgr mmgr,
    BRST_Xref xref)
{
    BRST_NameDict ndict;

    BRST_PTRACE(" BRST_NameDict_New\n");

    ndict = BRST_Dict_New(mmgr);
    if (!ndict)
        return NULL;

    if (BRST_Xref_Add(xref, ndict) != BRST_OK)
        return NULL;

    ndict->header.obj_class |= BRST_OSUBCLASS_NAMEDICT;

    return ndict;
}

BRST_NameTree
BRST_NameDict_NameTree(BRST_NameDict namedict,
    BRST_NameDictKey key)
{
    if (!namedict)
        return NULL;
    return BRST_Dict_Item(namedict, BRST_NAMEDICT_KEYS[key], BRST_OCLASS_DICT);
}

BRST_STATUS
BRST_NameDict_SetNameTree(BRST_NameDict namedict,
    BRST_NameDictKey key,
    BRST_NameTree ntree)
{
    return BRST_Dict_Add(namedict, BRST_NAMEDICT_KEYS[key], ntree);
}

BRST_BOOL
BRST_NameDict_Validate(BRST_NameDict namedict)
{
    if (!namedict)
        return BRST_FALSE;

    if (namedict->header.obj_class != (BRST_OSUBCLASS_NAMEDICT | BRST_OCLASS_DICT)) {
        BRST_Error_Set(namedict->error, BRST_INVALID_OBJECT, 0);
        return BRST_FALSE;
    }

    return BRST_TRUE;
}

/*------- EmbeddedFile -------*/
