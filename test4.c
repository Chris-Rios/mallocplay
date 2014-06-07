#include <stdio.h>
#include "my_malloc.h"
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#define malloc(x) my_malloc(x,__FILE__,__LINE__)
#define free(x) my_free(x,__FILE__,__LINE__)
/*this test case will try to free a pointer that was not returned by malloc*/
int main()
 {
	 char *r;
	 r=(char*)malloc(200);
	 r[0]='Z';
	 r[2]='P';
	 r[3]='D';
	 free(r+10);
	 return 0;
 }
