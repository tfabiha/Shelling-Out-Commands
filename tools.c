#include <stdio.h>
#include <stdlib.h>

#include "tools.h"

int run_multiple_cmd(char *ary){
  while(*ary){
    printf("%s\n", ary);
    ary++;
  }
}
