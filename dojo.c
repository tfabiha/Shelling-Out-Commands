#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv){
  while(1)
    {
      char str[60];
      printf("this is working\n");

      if (fgets(str, 60, stdin) != NULL)
	{
	  printf("I got this from you: %s\n", str);
	  return 0;
	}

    }
}
