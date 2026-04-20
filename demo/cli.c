#include "cli.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

char _fname[FNAME_BUFFER_SIZE];

char* prepare_output(int argc, char** argv) {
  if (argc > 0 && argv[0] != NULL) {
      int written = snprintf(_fname, FNAME_BUFFER_SIZE, "%s.pdf", argv[0]);
      if (written < 0 || written >= FNAME_BUFFER_SIZE) {
          printf("Error: program name too long for buffer\n");
          return NULL;
      }
  } else {
      strncpy(_fname, "output.pdf", FNAME_BUFFER_SIZE - 1);
      _fname[FNAME_BUFFER_SIZE - 1] = '\0';
  }
  return (char*)&_fname;
}
