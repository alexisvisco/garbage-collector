#include "gc.h"

int   main(int argc, char *argv[])
{
	gc_init(&argc);
	printf("Start stack: %d %d\n", GC_G.stack_start, &argc);
	void* hello = gc_alloc(10);
	hello--;

	// for(int i = 0 ; i < P_MAP_SIZE; i++) {
	// 	printf("%d\n", i);
	// 	for(int j = 0; j < gc_list_size(GC_G.pointer_map[i]); j++) {
	// 		t_gc_list *e = gc_list_at(GC_G.pointer_map[i], j);
	// 		printf("-> %lu of %zu\n", e->data.start, e->data.size);
	// 	}
	// }

	uint8_t markBits[3] = { 0 };

	gc_mark(markBits);

	printf("%#x %#x %#x\n", markBits[0], markBits[1], markBits[2]);
}
