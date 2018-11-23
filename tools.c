#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tools.h"

char** parse_args( char* line ){

  char** args = calloc(256, sizeof(char**)); //Might need to edit 256

  for(int i = 0; line; i++){
    args[i] = strsep(&line, " ");

  }
  return args;
}

void trim(char *str){
  size_t size = strlen(str);
  str = str + size - 1;
  while(*str=='\n' || *str==' '){
    *str = '\0';
    str-=1;
  }
}

void run_command(char **ary){
  execvp(ary[0], ary);
}

int run_multiple_cmd(char **ary){
  for(int i = 0; ary[i]; i++){
    printf("%s\n", ary[i]);
  }
  return 0;
}

int countTokens(char **ary){ //a_a_a where _ is a space returns 3. a_a_a_ returns 4
  int i = sizeof(ary)/sizeof(ary[0]);
  return i;

}
