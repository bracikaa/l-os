#include "string.h"

void *memset(void* ptr, int value, size_t num)
{
	for(unsigned int i = 0; i < num; i++)
	{
		((char *)ptr)[i] = value;	
	}
	return ptr;
}

