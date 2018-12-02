#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>
#include <sys/stat.h>

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

void run_command_custom(char **ary, int fd){

  execvp(ary[0], ary);
  if(strcmp(ary[0], "")){
    dup2(fd, 1);
    printf("%s: command not found\n", ary[0]);
  }
  exit(EXIT_SUCCESS);
}


// int piping(char **ary){
//   char stuff[1024];
//   FILE *ps_in;
//   FILE *ps_out;
//   for(int i = 0; ary[i+1]; i++){
//     ps_in = popen(ary[i], "r");
//     ps_out = popen(ary[i+1], "w");
//
//     while (fgets(stuff, 1024, ps_in))
//       fputs(stuff, ps_out);
//     pclose(ps_in);
//     pclose(ps_out);
//   }
//   return 0;
//
// }

// int piping(char **ary){
//   int p[2],tmp;
//   for(int i = 0; ary[i+1]; i++){
//     pipe(p);
//     if(fork()){
// 				close(p[1]);
// 				tmp=dup(STDIN_FILENO);
// 				dup2(p[0],STDIN_FILENO);
// 				wait(0);
// 				dup2(tmp,STDIN_FILENO);
// 				close(p[0]);
// 		}else{
// 				close(p[0]);
// 				tmp=dup(STDOUT_FILENO);
// 				dup2(p[1],STDOUT_FILENO);
// 				run_command(ary[i]);
// 				dup2(tmp,STDOUT_FILENO);
// 				close(p[1]);
// 				exit(0);
// 		}
//   }
// }

void redirect_STDIN(char *ary){
  char** args = parse_args(ary, '<');
  char** cmds;
  int std_in = dup(STDIN_FILENO);
  int switcheroo = 0;
  for(int i = 1; args[i]; i++){
    char * filename = trim(args[i]);
    int read_file = open(filename, O_RDONLY);
    switcheroo = dup2(read_file, switcheroo);

    // struct stat file;
    // stat(filename, &file);
    // int size = file.st_size;
    // printf("%d\n", size);
    // write(read_file, stdin, size);

    int f = fork();
    if(f){
	    wait(&f);
	  }
	  else{
      cmds = parse_args(args[0], ' ');
      run_command(cmds);
	  }

      //file = open(trim(args[i]), O_RDONLY);
    }
  dup2(std_in, switcheroo);
  free(args);
}

void redirect_STDOUT(char *ary){
  char** args = parse_args(ary, '>');
  char** cmds;
  int std_out = dup(STDOUT_FILENO);
  int switcheroo = 1;
  int toTrunc = 0;
  for(int i = 0; args[i+1]; i++){
    int new_file = open(trim(args[i+1]), O_CREAT | O_WRONLY, 0664);
    switcheroo = dup2(new_file, switcheroo);

    if(i < 1){
      int f = fork();
      if(f){
  	    wait(&f);
  	  }
  	  else{
        cmds = parse_args(args[i], ' ');
        run_command_custom(cmds, std_out);
  	  }
    }
    else{
      //int c;
        dup2(std_out, switcheroo);
        char * filen = trim(args[i]);
        int read_file = open(filen, O_RDONLY, 0664);
        //printf("hi\n", trim(args[i]));
        struct stat file;
        stat(filen, &file);
        int size = file.st_size;
        //printf("%d\n", size);
        char store[size];
        read(read_file, store, size);
        //printf("%s\n", store);
        write(new_file, store, size);
        toTrunc = 1;
      }
    if(toTrunc){
      open(trim(args[i]), O_TRUNC | O_WRONLY, 0664);
    }
      //open(trim(args[i]), O_TRUNC | O_WRONLY, 0664);
  }
  dup2(std_out, switcheroo);
  free(args);
}

int run_multiple_cmd(char **ary){
  char** argy;
  for(int i = 0; ary[i]; i++){
    if(check_char_cmd(ary[i], '>')){
      redirect_STDOUT(ary[i]);
      //run_redirection(argy, 1);
    }
    else if(check_char_cmd(ary[i], '<')){
      redirect_STDIN(ary[i]);
      //run_redirection(argy, 0);
    }
    else if(check_char_cmd(ary[i], '>')){
      argy = parse_args(ary[i], '>');
      //run_redirection(argy, 0);
    }
    else if(check_char_cmd(ary[i], '|')){
      argy = parse_args(ary[i], '|');
      //piping(argy);

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
