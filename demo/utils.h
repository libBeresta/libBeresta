#ifndef __UTILS_H
#define __UTILS_H

#define BRST_snprintf snprintf

#if defined(__WIN32__) || defined(__WIN64__)
#define FILE_SEPARATOR "\\"
#else
#define FILE_SEPARATOR "/"
#endif // defined(__WIN32__) || defined(__WIN64__)

#endif /* __UTILS_H */
