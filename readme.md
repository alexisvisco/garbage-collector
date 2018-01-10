# Dezy Garbage Collector

This gc is write in C and it is a naive implementation of mark and sweep algorithm.

## Sample

```c
#include "gc.h"

void	sample(void **h)
{
	void **hello;
	void *hi;

	hello = gc_alloc(10);
	*hello = gc_alloc(11);
	*hello += 3;
	*h = *hello;
}

int		main(int argc, char *argv[])
{
	void *h;

	gc_init(&argc, 1);

	sample(&h);
	gc_alloc(1);
	
	gc_destroy();
}
```