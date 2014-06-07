#include <stdio.h>
#include "my_malloc.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define malloc(x) my_malloc(x,__FILE__,__LINE__)
#define free(x) my_free(x,__FILE__,__LINE__)
/*mallocs and frees normally, should be no problem, prints out what i malloced*/
int main()
 {
	 int* number;
	 char* chris= (char*)malloc(10);
	 chris[0] ='c';
	 chris[1] = 'm';
	 chris[2]='r';
	 chris[3]='\0';
	 number = (int*)malloc(4);
	 number[0]=24;
	 printf("Malloced number:%d\n",number[0]);
	 free(number);
	 char* danielle = (char *)malloc(10);
	 danielle[0] = 'd';
	 danielle[1]='a';
	 danielle[2]='o';
	 danielle[3]='\0';
	 printf("This is char array #1 that was malloced:%s\nThis is char array #2 that was malloced:%s\n",chris,danielle);
	 free(chris);
	 free(danielle);
	 return 0;
 }
