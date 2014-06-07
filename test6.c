#include <stdio.h>
#include "my_malloc.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define malloc(x) my_malloc(x,__FILE__,__LINE__)
#define free(x) my_free(x,__FILE__,__LINE__)
/*this case tests out my fragmentation checks*/
int main()
 {
	 char* number3 = (char*)malloc(40);
	 int* number = (int*)malloc(2400);
	 int* number2 = (int*)malloc(250);
	 number2[0]=25;
	 number[20] = 17;
	 number3[0]='Z';
	 printf("this is number1:%d and number 2 %d\n",number[20],number2[0]);
	 free(number);
	 free(number2);
	 printf("this is my char %c\n",number3[0]);
	 free(number3);
	 return 0;
 }
