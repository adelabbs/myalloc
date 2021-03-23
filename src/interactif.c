#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
   	char optstring[]="abcf";  // options permises -a -b et -c
   	int c;
   	printf("-%c\n",(char) c); 
   	
   	while( (c=getopt (argc, argv, optstring)) != EOF )
   {
           // on affiche ces options
          printf("-%c\n",(char) c); 
          //interactiveMode();
   }
   
   // on affiche le premier argument.
   printf("%s\n",argv[optind]); 
   
	//long n;
	//snprintf(chaine, sizeof chaine, "%llu", n);
 	//interactiveMode();
 //	scanf("%s", &command);		
 //	printf("%s\n", command);
 //	if sscanf

   	return 0;
}

/*void interactiveMode(){
 	 printf("TOTAL SPACE = %d\n", getMemorySize(memory));
 	 printf("AVAILABLE SPACE = %d\n", getMemoryAvailableSpace(memory));
	  printf("Block\t|Position\t|Size\n");
	  BlockList bl = memory.blocks;
	  int i = 0;
 	 while(!isEmptyBlockList(bl)){
 	   printf("%d\t\t| %d\t\t\t| %d\n", i, getBlockPosition(bl), getBlockSize(bl));
 	   i++;
 	   bl = getNextBlock(bl);
	  }
	 printf("--------------------------\n");
 	 printf("TO OPEN BATCH MODE, PLEASE TYPE: '-b'");
 	 printf("--------------------------\n");
 	 printf("TO OPEN CLI MODE, PLEASE TYPE: '-c'");
 	 printf("--------------------------\n");
 	 printf("TO ALLOCATE MEMORY, PLEASE TYPE: '-a -i', WITH I THE SIZE OF YOUR BLOCK");
 	 printf("--------------------------\n");
 	 printf("TO DELETE A BLOCK, PLEASE TYPE: '-f -i', WITH I THE POSITION OF YOUR BLOCK");
} */
