#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

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

  char * new_str = malloc(size);
  int str_count = 0;
  char * point_org = orig;

  int space_counter = 0;


  while (*point_org)
  {
    //printf("Got here!\n");
    if (*point_org == ' ' && space_counter)
    {
      point_org++;
    }
    else
    {
      space_counter = *point_org == ' ';

      if(new_str[str_count] != ' '){
        new_str[str_count] = *point_org;

      }
      point_org++;
      str_count++;
    }

  }

  new_str[str_count] = '\0';

  return new_str;
}

void run_command(char **ary){

  execvp(ary[0], ary);
  if(strcmp(ary[0], "")){
    printf("%s: command not found\n", ary[0]);
  }
  exit(EXIT_SUCCESS);
}

void run_redirection(char **ary, int direction){ // 1: >, 0: <
}

int piping(char *ary){
  char** argy = parse_args(ary, '|');
  char stuff[1024];
  FILE *ps_in;
  FILE *ps_out;
  for(int i = 0; argy[i]; i++){
    ps_in = popen(argy[i], "r");
    ps_out = popen(argy[i+1], "w");

    while (fgets(stuff, 1024, ps_in))
      fputs(stuff, ps_out);
    pclose(ps_in);
    pclose(ps_out);
  }
  return 0;

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
