#include <stdio.h>
#include "my_malloc.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define malloc(x) my_malloc(x,__FILE__,__LINE__)
#define free(x) my_free(x,__FILE__,__LINE__)

/*this test case checks for something being free'ed that was never allocated, in this case an int* */
int main()
 {
	 int *p;
	 free(p);
	 return 0;
 }
