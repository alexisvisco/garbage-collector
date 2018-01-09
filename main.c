#include "gc.h"


int lol() {
	void** hello = gc_alloc(10);
	*hello = gc_alloc(11);
	gc_free(*hello);
}

int   main(int argc, char *argv[])
{
	gc_init(&argc, 1);
	lol();
	gc_alloc(1);

}
