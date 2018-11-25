#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "tools.h"

char** parse_args(char* line, char c){
  //printf("%s, %c\n", line, c);
  line = trim(line);
  // printf("Gucci Pipe: %d\n", check_char_cmd(line, '|'));
  // printf("Gucci >: %d\n", check_char_cmd(line, '>'));
  // printf("Gucci <: %d\n", check_char_cmd(line, '<'));
  char** args = calloc(256, sizeof(char**)); //Might need to edit 256
  int i = 0;
  if(check_char_cmd(line, c)){
    while ((args[i] = strsep(&line, &c)) != NULL){
      i++;
    }
  }
  else{
    args[0] = line;
  }
  // for(int i = 0; args[i]; i++){
  //   printf("%s\n", args[i]);
  // }

  //printf("%s, %s, %c\n", args[0], args[1], c);
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
  //printf("%s\n", ary[1]);
  execvp(ary[0], ary);
}

int run_multiple_cmd(char **ary){
  for(int i = 0; ary[i]; i++){
    //printf("%s\n", ary[i]);
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
