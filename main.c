#include "gc.h"

int   main(int argc, char *argv[])
{
	gc_init(&argc);
	printf("Start stack: %d %d\n", GC_G.stack_start, &argc);
	void** hello = gc_alloc(10);
	*hello = gc_alloc(11);

	gc_run();
}
