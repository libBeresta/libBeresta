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
#include "brst_page.h"
#include "brst_array.h"
#include "brst_embedded_file.h"
#include "private/brst_embedded_file.h"
#include "private/brst_array.h"
#include "private/brst_utils.h"
#include "brst_outline.h"
#include "brst_pdfa.h"
#include "private/brst_encrypt_dict.h"
#include "brst_destination.h"
#include "private/brst_catalog.h"
#include "private/brst_doc.h"
#include "brst_base.h"

BRST_EXPORT(BRST_EmbeddedFile)
BRST_Doc_AttachFile(BRST_Doc pdf,
    BRST_CSTR file)
{
    BRST_NameDict names;
    BRST_NameTree ntree;
    BRST_EmbeddedFile efile;
    BRST_String name;
    BRST_Array af;
    BRST_STATUS ret = BRST_OK;

    BRST_PTRACE(" BRST_AttachFile\n");

    if (!BRST_Doc_Initialized(pdf))
        return NULL;

    names = BRST_Catalog_Names(pdf->catalog);
    if (!names) {
        names = BRST_NameDict_New(pdf->mmgr, pdf->xref);
        if (!names)
            return NULL;

        ret = BRST_Catalog_SetNames(pdf->catalog, names);
        if (ret != BRST_OK)
            return NULL;
    }

    // TODO Это, скорее всего, уже реализация версии PDF 2.0.
    // В 1.7 этого нет -- надо увести под условную компиляцию.
    ntree = BRST_NameDict_NameTree(names, BRST_NAME_EMBEDDED_FILES);
    if (!ntree) {
        ntree = BRST_NameTree_New(pdf->mmgr, pdf->xref);
        if (!ntree)
            return NULL;

        ret = BRST_NameDict_SetNameTree(names, BRST_NAME_EMBEDDED_FILES, ntree);
        if (ret != BRST_OK)
            return NULL;
    }

    efile = BRST_EmbeddedFile_New(pdf->mmgr, pdf->xref, file);
    if (!efile)
        return NULL;

    name = BRST_String_New(pdf->mmgr, file, NULL);
    if (!name)
        return NULL;

    ret = BRST_NameTree_Add(ntree, name, efile);
    if (ret != BRST_OK)
        return NULL;

    af = BRST_Dict_Item(pdf->catalog, "AF", BRST_OCLASS_ARRAY);
    if (!af) {
        af = BRST_Array_New(pdf->mmgr);
        if (!af)
            return NULL;
        BRST_Dict_Add(pdf->catalog, "AF", af);
    }
    BRST_Array_Add(af, efile);

    pdf->pdf_version = (pdf->pdf_version > BRST_VER_17 ? pdf->pdf_version : BRST_VER_17);
    return efile;
}
