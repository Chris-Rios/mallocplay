#include <stdio.h>
#include "my_malloc.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define malloc(x) my_malloc(x,__FILE__,__LINE__)
#define free(x) my_free(x,__FILE__,__LINE__)
/*this test case, frees memory, mallocs it again, and then frees it again, then tries
 * to free again with no malloc, and will give an error*/
int main()
 {
	 int* number = (int*)malloc(4);
	 number[0]=14;
	 free(number);
	 number = (int*)malloc(4);
	 free(number);
	 free(number);
	 return 0;
 }
