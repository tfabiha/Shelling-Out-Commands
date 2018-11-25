#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "tools.h"

int main(int argc, char **argv){

  while(1)
  {
    char cmds[100];
    char cwd[1024];
    getcwd(cwd, sizeof(cwd));
    printf("\033[32m%s \033[0m \033[31mDojo:\033[0m \033[35m$\033[0m \033[34m",cwd);
    if (fgets(cmds, 60, stdin) == NULL)
    {
      printf("Error has been found. Exiting.\n");
    }
    else
    {
      if (strcmp(cmds, "exit\n") == 0)
      {
        printf("exiting\n");
        return 0;
      }
      // if (strcmp(cmds, "exit\n") == 0) FOR CODING CD
      // {
      //   printf("exiting\n");
      //   return 0;
      // }
      char** _args = parse_args(cmds, ';');
      // for(int i = 0; _args[i]; i++){
      //   printf("%s\n", _args[i]);
      // }
      int n_tokens = countTokens(_args);
      if(n_tokens > 0){
          run_multiple_cmd(_args);
      }

      //run_multiple_cmd(_args);
    }

  }
  //}
  return 0;
}
