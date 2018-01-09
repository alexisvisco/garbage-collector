#define GC_PTR_LIMIT 1

#include "gc.h"


int lol() {
	void** hello = gc_alloc(10);
	*hello = gc_alloc(11);

}

int   main(int argc, char *argv[])
{
	gc_init(&argc);
	printf("Start stack: %d %d\n", GC_G.stack_start, &argc);

	lol();
	gc_alloc(1);
}
