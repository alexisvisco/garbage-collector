#include "gc.h"

int   main()
{
	gc_init();
	printf("Start stack: %p\n", GC_G.stack_start);
	gc_alloc(10);
	gc_alloc(11);
	gc_alloc(12);
	gc_alloc(13);
	gc_alloc(10);
	gc_alloc(11);
	gc_alloc(12);
	gc_alloc(13);
	gc_alloc(10);
	gc_alloc(11);
	gc_alloc(12);
	gc_alloc(13);
	gc_alloc(10);
	gc_alloc(11);
	gc_alloc(12);
	gc_alloc(13);
	gc_alloc(10);
	gc_alloc(11);
	gc_alloc(12);
	gc_alloc(13);
	gc_alloc(10);
	gc_alloc(11);
	gc_alloc(12);
	gc_alloc(13);

	for(int i = 0 ; i < P_MAP_SIZE; i++) {
		printf("%d\n", i);
		for(int j = 0; j < gc_list_size(GC_G.pointer_map[i]); j++) {
			t_gc_list *e = gc_list_at(GC_G.pointer_map[i], j);
			printf("-> %p of %zu\n", e->data.start, e->data.size);
		}
	}

	uint8_t[] markBits = { 0 };

	gc_mark()
}
