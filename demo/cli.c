#include "cli.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

char _fname[FNAME_BUFFER_SIZE];

char* prepare_output(int argc, char** argv) {
  if (argc > 0 && argv[0] != NULL) {
      size_t src_len = strnlen(argv[0], FNAME_BUFFER_SIZE);

      // Проверка, что имя программы не слишком длинное
      if (src_len > FNAME_BUFFER_SIZE - 5) { // -5 для ".pdf" и нулевого байта
          return NULL;
      }

      // Безопасное копирование имени программы
      BRST_snprintf(_fname, FNAME_BUFFER_SIZE, "%s.pdf", argv[0]);

  } else {
      // Имя по умолчанию, если argv[0] недоступен
      BRST_snprintf(_fname, FNAME_BUFFER_SIZE, "%s", "output.pdf");
  }

  return (char*)&_fname;
}

void print_error(const char* message) {
    fputs("Error: ", stderr);
    fputs(message, stderr);
    fputc('\n', stderr);
}