#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "tools.h"

int main(int argc, char **argv){

  while(1)
  {
    char cmds[100];
    printf("Dojo:$ ");
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
      trim(cmds);
      char** _args = parse_args_commas(cmds);
      int n_tokens = countTokens(_args);
      if(n_tokens > 0){
        int f = fork();
        if(f){
          wait(&f);
        }
        else{
          run_multiple_cmd(_args);
        }
      }

      //run_multiple_cmd(_args);
    }

  }
  //}
  return 0;
}
