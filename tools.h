#ifndef TOOLS_H
#define TOOLS_H

int run_multiple_cmd(char**ary);

char** parse_args(char* line, char c);

char** parse_args_custom(char** args);

int countTokens(char **ary);

char* trim(char *str);

void run_command(char **ary);

void run_command_custom(char **ary, int fd);

void redirect_STDIN(char *ary);

void redirect_STDOUT(char *ary);

void redirect_pipes(char* ary);

int check_char_cmd(char *ary, char c);

void piping(char *ary);
#endif
