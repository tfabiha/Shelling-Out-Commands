#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

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

  return args;
}

char* trim(char *str){
  size_t size = strlen(str);
  char * orig = str;
   while(*orig=='\n' || *orig==' '){
     orig++;
   }
   str = str + size - 1;
   while(*str=='\n' || *str==' '){
     *str = '\0';
     str-=1;
   }
   return orig;
}

void run_command(char **ary){
  execvp(ary[0], ary);
  exit(EXIT_SUCCESS);
}

void run_redirection(char **ary, int direction){ // 1: >, 0: <
  int new_file = open(trim(ary[1]), O_CREAT | O_WRONLY, 0666);
  if(direction){ // >
    int std_out = dup(1);
    dup2(new_file, 1);
    int f = fork();
	  if(f){
	    wait(&f);
	  }
	  else{
      run_command(ary);
	  }

  }
  else{ // <

  }
}

void run_pipe(char **ary){

}

int run_multiple_cmd(char **ary){
  char** argy;
  for(int i = 0; ary[i]; i++){
    if(check_char_cmd(ary[i], '>')){
      argy = parse_args(ary[i], '>');
      run_redirection(argy, 1);
    }
    else if(check_char_cmd(ary[i], '<')){
      argy = parse_args(ary[i], '<');
      run_redirection(argy, 0);
    }
    else if(check_char_cmd(ary[i], '|')){
      argy = parse_args(ary[i], '|');
      run_pipe(argy);
    }

    else{
      argy = parse_args(ary[i], ' ');

      if (strcmp(argy[0], "exit") == 0)
      {
        printf("exiting\033[0m\n");
        free(argy);

        exit(EXIT_SUCCESS);
      }

      if (strcmp(argy[0], "cd") == 0)
      {
        chdir(argy[1]);
      }
      else
      {
        int f = fork();
        if(f){
          wait(&f);
        }
        else{
          run_command(argy);
        }
      }
    }
    free(argy);
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
