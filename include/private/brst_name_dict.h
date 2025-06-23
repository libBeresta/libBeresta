#ifndef PRIVATE_BRST_NAME_DICT_H
#define PRIVATE_BRST_NAME_DICT_H

#include "private/brst_dict.h"
#include "private/brst_name_tree.h"

typedef BRST_Dict BRST_NameDict; 

/* Name Dictionary values -- see PDF reference section 7.7.4 */
typedef enum _BRST_NameDictKey {
    BRST_NAME_DESTS,
    BRST_NAME_AP,
    BRST_NAME_JAVASCRIPT,
    BRST_NAME_PAGES,
    BRST_NAME_TEMPLATES,
    BRST_NAME_IDS,
    BRST_NAME_URLS,
    BRST_NAME_EMBEDDED_FILES,
    BRST_NAME_ALTERNATE_PRESENTATIONS,
    BRST_NAME_RENDITIONS,
    BRST_NAME_EOF
} BRST_NameDictKey;


BRST_NameDict
BRST_NameDict_New(
    BRST_MMgr mmgr,
    BRST_Xref xref
);

BRST_NameTree
BRST_NameDict_NameTree(
    BRST_NameDict    namedict,
    BRST_NameDictKey key
);

BRST_STATUS
BRST_NameDict_SetNameTree(
    BRST_NameDict    namedict,
    BRST_NameDictKey key,
    BRST_NameTree    tree
);

BRST_BOOL
BRST_NameDict_Validate(
    BRST_NameDict namedict
);

#endif /* PRIVATE_BRST_NAME_DICT_H */