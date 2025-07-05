#define BRST_LIBRARY_NAME "libBeresta"
#define BRST_MAJOR_VERSION 1
#define BRST_MINOR_VERSION 0
#define BRST_BUGFIX_VERSION 0
#define BRST_EXTRA_VERSION ""

#define brst_vquote(x) #x
#define brst_vexp(x) brst_vquote(x)

#define BRST_VERSION_TEXT (brst_vexp(BRST_MAJOR_VERSION) "." brst_vexp(BRST_MINOR_VERSION) "." brst_vexp(BRST_BUGFIX_VERSION) BRST_EXTRA_VERSION)
#define BRST_VERSION_ID ((BRST_MAJOR_VERSION) * 10000 + (BRST_MINOR_VERSION) * 100 + (BRST_BUGFIX_VERSION))
