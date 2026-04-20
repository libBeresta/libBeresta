#include "cli.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

char _fname[FNAME_BUFFER_SIZE];

char* prepare_output(int argc, char** argv) {
  if (argc > 0 && argv[0] != NULL) {
      size_t src_len = strlen(argv[0]);

      // Проверка, что имя программы не слишком длинное
      if (src_len > FNAME_BUFFER_SIZE - 5) { // -5 для ".pdf" и нулевого байта
          printf("Error: program name too long\n");
          return NULL;
      }

      // Безопасное копирование имени программы
      strncpy(_fname, argv[0], FNAME_BUFFER_SIZE - 1);
      _fname[FNAME_BUFFER_SIZE - 1] = '\0';

      // Безопасное добавление расширения
      strncat(_fname, ".pdf", FNAME_BUFFER_SIZE - strlen(_fname) - 1);
  } else {
      // Имя по умолчанию, если argv[0] недоступен
      strncpy(_fname, "output.pdf", FNAME_BUFFER_SIZE - 1);
      _fname[FNAME_BUFFER_SIZE - 1] = '\0';
  }

  return (char*)&_fname;
}

void print_error(const char* message) {
    fputs("Error: ", stderr);
    fputs(message, stderr);
    fputc('\n', stderr);
}