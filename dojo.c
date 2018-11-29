#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "tools.h"

int main(int argc, char **argv){

  while(1)
  {
    char cmds[100];
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\033[31mDojo:\033[0m\033[32m%s\033[0m\033[35m$\033[0m\033[38;5;206m ",cwd);
    if (fgets(cmds, 60, stdin) == NULL)
    {
      printf("Error has been found. Exiting.\n");
    }
    else
    {
      // if (strcmp(cmds, "exit\n") == 0)
      // {
      //   printf("exiting\033[0m\n");
      //   return 0;
      // }
      char** _args = parse_args(cmds, ';');
      // for(int i = 0; _args[i]; i++){
      //   printf("%s\n", _args[i]);
      // }
      int ext = 0;

      int n_tokens = countTokens(_args);
      if(n_tokens > 0){
          ext = run_multiple_cmd(_args);

          if (ext)
            return 0;
      }

    }

  }
  //}
  return 0;
}
