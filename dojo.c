#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <errno.h>
#include <signal.h>

#include "tools.h"

static void sighandler(int signo)
{
  if (signo == SIGINT)
  {
    printf("\033[0m\n");
    exit(EXIT_SUCCESS);
  }
}

int main(int argc, char **argv){

  while(1)
  {
    signal(SIGINT, sighandler);

    char cmds[100];
    char cwd[1024];

    getcwd(cwd, sizeof(cwd));
    printf("\033[31mDojo:\033[0m\033[32m%s\033[0m\033[35m$\033[0m\033[38;5;206m ",cwd);

    if (fgets(cmds, 60, stdin) == NULL)
    {
      printf("Error has been found. Exiting.\n");
      exit(EXIT_FAILURE);
    }
    else
    {
      char** _args = parse_args(cmds, ';');
      int n_tokens = countTokens(_args);

      if(n_tokens > 0){
          run_multiple_cmd(_args);
      }
    }
  }

  return 0;
}
