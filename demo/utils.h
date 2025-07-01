#ifndef __UTILS_H
#define __UTILS_H

#if defined(__WIN32__) || defined(__WIN64__)
#define BRST_snprintf _snprintf
#define FILE_SEPARATOR "\\"
#else
#define BRST_snprintf snprintf
#define FILE_SEPARATOR "/"
#endif // defined(__WIN32__) || defined(__WIN64__)

// То же самое, что и ÓÔŐÖ×ŘŮ, но в кодировке ISO8859-2
static const char iso8859_2_text[8] = "\xD3\xD4\xD5\xD6\xD7\xD8\xD9\x00";

#endif /* __UTILS_H */