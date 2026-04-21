#ifndef __CLI_H
#define __CLI_H

#define FNAME_BUFFER_SIZE 4096
extern char _fname[];
char* prepare_output(int argc, char** argv);
void print_error(const char* message);

#endif /* __CLI_H */
