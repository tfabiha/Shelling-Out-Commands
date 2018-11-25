#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tools.h"

char** parse_args(char* line, char c){
  line = trim(line);
  // printf("Gucci Pipe: %d\n", check_char_cmd(line, '|'));
  // printf("Gucci >: %d\n", check_char_cmd(line, '>'));
  // printf("Gucci <: %d\n", check_char_cmd(line, '<'));
  char** args = calloc(256, sizeof(char**)); //Might need to edit 256

  for(int i = 0; line; i++){
    args[i] = strsep(&line, &c);

  }
  return args;
}

char* trim(char *str){
  size_t size = strlen(str);
  char * orig = str;
  while(*orig=='\n' || *orig==' ' || *orig=='\t'){
    orig++;
  }
  str = str + size - 1;
  while(*str=='\n' || *str==' ' || *str=='\t'){
    *str = '\0';
    str-=1;
  }
  return orig;
}

void run_command(char **ary){
  execvp(ary[0], ary);
}

int run_multiple_cmd(char **ary){
  for(int i = 0; ary[i]; i++){
    char** argy = parse_args(ary[i], ' ');
    int f = fork();
    if(f){
      wait(&f);
    }
    else{
      run_command(argy);
      free(argy);
    }
  }
  return 0;
}

int countTokens(char **ary){ //a_a_a where _ is a space returns 3. a_a_a_ returns 4
  int i = sizeof(ary)/sizeof(ary[0]);
  return i;

}

int check_char_cmd(char *ary, char c){ //Returns 1 (True) if c in ary, else 0 (False)
  while(*ary){
    if(*ary == c){
      return 1;
    }
    ary++;
  }
  return 0;
}
