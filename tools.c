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
  size_t size = strlen(line);
  char** args = calloc(size, sizeof(char*)); //Might need to edit 256
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


void piping(char *ary){
  char** args = parse_args(ary, '|');

  int count = 0;

  int reg_in = dup(STDIN_FILENO);
  int reg_out = dup(STDOUT_FILENO);

  for (int i = 0; args[i]; i++)
    {
      count++;
    }

  int * fd[count];
  //printf("Count: %d\n", count);

  for (int i = 0; i < count; i++)
    {
      fd[i] = (int *) malloc(2 * sizeof(int));
      pipe(fd[i]);
    }

  FILE * input;
  FILE * output;
  char buffer[256];

  output = popen(args[0], "r");
  input = popen(args[1], "w");

  while(fgets(buffer, 256, output))
    {
      fputs(buffer, input);
    }

  pclose(output);
  pclose(input);


  /* for (int i = 0; i < count; i++) */
  /*   { */
  /*     if (i == 0) */
  /* 	{ */
  /* 	  int f = fork(); */

  /* 	  if (f) */
  /* 	    { */
  /* 	      wait(&f); */
  /* 	    } */
  /* 	  else */
  /* 	    { */
  /* 	      dup2(fd[i][1], STDOUT_FILENO); */
  /* 	      close(fd[i][0]); */

  /* 	      char** _args = parse_args(args[i], ' '); */
  /* 	      run_command(_args); */
  /* 	      free(_args); */
  /* 	    } */
  /* 	} */
  /*     else if (i == count - 1) */
  /* 	{ */
  /* 	  printf("I am at my last point\n"); */
  /* 	  int f = fork(); */

  /* 	  if (f) */
  /* 	    { */
  /* 	      wait(&f); */
  /* 	    } */
  /* 	  else */
  /* 	    { */
  /* 	      printf("I am the child\n"); */
  /* 	      dup2(fd[i-1][0], STDIN_FILENO); */
  /* 	      close(fd[i-1][1]); */

  /* 	      char** _args = parse_args(args[i], ' '); */
  /* 	      run_command(_args); */
  /* 	      free(_args); */

  /* 	      exit(EXIT_SUCCESS); */
  /* 	    } */
  /* 	} */
  /*     else */
  /* 	{ */
  /* 	  int f = fork(); */

  /* 	  if (f) */
  /* 	    { */
  /* 	      wait(&f); */
  /* 	    } */
  /* 	  else */
  /* 	    { */
  /* 	      dup2(fd[i-1][0], STDIN_FILENO); */
  /* 	      close(fd[i-1][1]); */

  /* 	      dup2(fd[i][1], STDOUT_FILENO); */
  /* 	      close(fd[i][0]); */

  /* 	      char** _args = parse_args(args[i], ' '); */
  /* 	      run_command(_args); */
  /* 	      free(_args); */
  /* 	    } */
  /* 	} */
  /*   } */

  /* dup2(reg_out, STDOUT_FILENO); */
  /* dup2(reg_in, STDIN_FILENO); */

  /* printf("It got to the end. It's working.\n");
 */

  //
  // for(int i = 0; args[i]; i++){
  //   pipe(fds);
  //
  //   int f = fork();
  //
  //   printf("%s\n", "i got to here");
  //   if(f){
  //     wait(&f);
  //     close(fds[1]);
  //     s = dup(STDIN_FILENO);
  //     dup2(STDOUT_FILENO, STDIN_FILENO);
  //
  // 	}
  //   else{
  //     printf("%s\n", "Im a child");
  //     close(fds[0]);
  //     dup2(fds[1], STDOUT_FILENO);
  //
  //     char** _args = parse_args(args[i], ' ');
  //     run_command(_args);
  //     free(_args);
  //     close(fds[1]);
  // 	}
  // }
  // free(args);
}

void redirect_STDIN(char *ary){
  char** args = parse_args(ary, '<');
  char** cmds;
  if(args[0]){
    cmds = parse_args(args[0], ' ');
    //printf("%s\n", cmds[0]);
  }
  int std_in = dup(STDIN_FILENO);
  int switcheroo = 0;

  for(int i = 1; args[i]; i++){
    char * filename = trim(args[i]);
    int read_file = open(filename, O_RDONLY);
    switcheroo = dup2(read_file, switcheroo);

    int f = fork();
    if(f){
      wait(&f);
    }
    else{
      run_command(cmds);
    }

  }
  free(cmds);
  dup2(std_in, 0);
  free(args);
}

void redirect_STDOUT(char *ary){
  char** args = parse_args(ary, '>');
  char** cmds;
  int std_out = dup(STDOUT_FILENO);
  int switcheroo = 1;
  int toTrunc = 0;
  for(int i = 0; args[i+1]; i++){
    char * filen = trim(args[i]);
    int read_file = open(filen, O_RDONLY, 0664);
    int new_file = open(trim(args[i+1]), O_CREAT | O_WRONLY, 0664);
    switcheroo = dup2(new_file, switcheroo);

    //printf("%d\n", read_file);
    if(i < 1 && !(read_file+1)){
      int f = fork();
      if(f){
	      wait(&f);
      }
      else{
        cmds = parse_args(args[i], ' ');
        run_command_custom(cmds, std_out);
        free(cmds);
      }
    }
    else{
      //int c;
      dup2(std_out, 1);
      
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


void redirect_pipes(char* ary){
  char **args = parse_args(ary, ' ');
  parse_args_custom(args);
}

void parse_args_custom(char** args){
  // printf("Gucci Pipe: %d\n", check_char_cmd(line, '|'));
  // printf("Gucci >: %d\n", check_char_cmd(line, '>'));
  // printf("Gucci <: %d\n", check_char_cmd(line, '<'));

  char* arg = calloc(1, sizeof(char));

  for(int i = 0; args[i]; i++){

      if(strcmp(args[i], ">")==0){

        while(args[i] && strcmp(args[i], "|") != 0 && strcmp(args[i], "<") != 0){
          strcat(arg, " ");
          int size = strlen(args[i]) + strlen(arg);
          arg = realloc(arg, size);
          strcat(arg, args[i]);
          i++;
        }
        printf("%s\n", arg);
        redirect_STDOUT(arg);
        free(arg);
        arg = calloc(1, sizeof(char));
        if(args[i]){
          //printf("%s\n", arg);
          i-=2;
          //printf("%d\n", i);
        }
      }
      else if(strcmp(args[i], "<") == 0){

        while(args[i] && strcmp(args[i], "|") != 0 && strcmp(args[i], ">") != 0){
          strcat(arg, " ");
          int size = strlen(args[i]) + strlen(arg);
          arg = realloc(arg, size);
          strcat(arg, args[i]);
          i++;
        }
        printf("%s\n", arg);
        redirect_STDIN(arg);
        free(arg);
        arg = calloc(1, sizeof(char));
        if(args[i]){
          i-=2;
        }
      }

      else{
        strcat(arg, " ");
        int size = strlen(args[i]) + strlen(arg);
        arg = realloc(arg, size);
        strcat(arg, args[i]);
      }
      // if(strcmp(args[i], ">")){
      //
      // }
  }
  free(args);
}


int run_multiple_cmd(char **ary){
  char** argy;
  for(int i = 0; ary[i]; i++){
    if(check_char_cmd(ary[i], '>')){
      //redirect_STDOUT(ary[i]);
      redirect_pipes(ary[i]);
      //run_redirection(argy, 1);
    }
    else if(check_char_cmd(ary[i], '<')){
      redirect_STDIN(ary[i]);
      //run_redirection(argy, 0);
    }
    else if(check_char_cmd(ary[i], '|')){
      piping(ary[i]);

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
