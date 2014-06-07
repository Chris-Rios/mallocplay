#include <stdlib.h>
#define malloc(x) my_malloc(x,__FILE__,__LINE__)
#define free(x) my_free(x,__FILE__,__LINE__)
#define BLOCKSIZE 5000
void* my_malloc(unsigned int size,char* file, int line);
void my_free(void *p,char* file, int line );
struct MemEntry
{
	struct MemEntry *prev,*succ;
	int isfree;
	int size;
	char marker;
};

