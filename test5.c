#include <stdio.h>
#include "my_malloc.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define malloc(x) my_malloc(x,__FILE__,__LINE__)
#define free(x) my_free(x,__FILE__,__LINE__)
/*this test case tries to malloc with size that is bigger than memory size*/
int main()
 {
	 int* number = (int*)malloc(5001);
	 return 0;
 }
