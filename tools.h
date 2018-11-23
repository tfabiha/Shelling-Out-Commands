#ifndef TOOLS_H
#define TOOLS_H

int run_multiple_cmd(char**ary);

char** parse_args(char* line);

int countTokens(char **ary);

void trim(char *str);

void run_command(char **ary);

#endif
