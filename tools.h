#ifndef TOOLS_H
#define TOOLS_H

int run_multiple_cmd(char**ary);

char** parse_args_spaces(char* line);

char** parse_args_commas(char* line);

int countTokens(char **ary);

char* trim(char *str);

void run_command(char **ary);

#endif
