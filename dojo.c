#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "tools.h"

int main(int argc, char **argv){
  char*arg = malloc(20);
    arg = "This is cool";
  char** _args = parse_args(arg);
  //run_multiple_cmd(_args);
  while(1)
    {
      char str[60];
      printf("Dojo:$ ");

      if (fgets(str, 60, stdin) == NULL)
	{
	  printf("Error has been found. Exiting.\n");
	  
	}

      if (strcmp(str, "exit\n") == 0)
	{
	  printf("exiting\n");
	  return 0;
	}

      

    }
}
