#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#define FNAME_SIZE 256
#include <string.h>

#define TEST_NAME(a) if (argc == 2 && strcmp(argv[1], "-n") == 0) {printf("%s\n", a); return 0; }

#endif