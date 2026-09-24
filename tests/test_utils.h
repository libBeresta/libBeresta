#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#define FNAME_SIZE 4096
#include <string.h>
#include <stdio.h>

#define TEST_NAME(a) if (argc == 2 && strcmp(argv[1], "-n") == 0) {printf("%s\n", a); return 0; }
#define BRST_snprintf snprintf

#endif