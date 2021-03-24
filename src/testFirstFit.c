#include <stdio.h>
#include <stdlib.h>
#include "memory.h"

extern char *optarg;
extern int optind;

/*Test*/
int main(){
  int sizeMax = 50;
  int myBloc = 25;
  initMemory(sizeMax);
  firstFit(myBloc);
  displayMemorySpace();
  return 0;
}