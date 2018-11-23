#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "tools.h"

int main(int argc, char **argv){
  char cmds[100];
  fgets(cmds, 100, stdin);
  trim(cmds);
  char** _args = parse_args(cmds);
  run_multiple_cmd(_args);
  printf("%d\n", countTokens(_args));
  // while(1)
  // {
  //  char str[60];
  //  printf("Dojo:$ ");
  //
  //  if (fgets(str, 60, stdin) == NULL)
  // {
  //  printf("Error has been found. Exiting.\n");
  //
  // }
  //
  //  if (strcmp(str, "exit\n") == 0)
  // {
  //  printf("exiting\n");
  //  return 0;
  // }



  //}
  return 0;
}
