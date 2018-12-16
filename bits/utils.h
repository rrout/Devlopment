#include <stdio.h>

#define MY_SIZEOF_VAR(var)				(size_t) (((char *)&var +1) - (char *)&var)
#define MY_SIZEOF_TYPE(type)			(size_t) (((type *)0)+1)
#define MY_OFFSETOF(struct, elem)		(size_t) (((struct *)0)->elem)


