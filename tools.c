#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

char** parse_args( char* line ){
 
  char** args = calloc(256, sizeof(char**)); //Might need to edit 256

  for(int i = 0; line; i++){
    args[i] = strsep(&line, " ");

  }
  return args;
}

int run_multiple_cmd(char **ary){
  printf("%s\n", ary[0]);
  
  for(int i = 0; ary[i]; i++){
    printf("%s\n", ary[i]);
  }
}
