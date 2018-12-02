#ifndef TOOLS_H
#define TOOLS_H

int run_multiple_cmd(char**ary);

char** parse_args(char* line, char c);

int countTokens(char **ary);

char* trim(char *str);

void run_command(char **ary);

void redirect_STDOUT(char *ary);

int check_char_cmd(char *ary, char c);

int piping(char **ary);
#endif
