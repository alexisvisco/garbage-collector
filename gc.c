#include "gc.h"

#define STACK_PT ({ char sp; &sp; })
#define HASH(ptr) ((uintptr_t)ptr >> 3)
#define SET_BIT(l, i, v) (l[i/8] |= 1 << (i % 8))
#define SWAP(type, a,b) { type tmp; tmp = a; a = b; b = tmp; }

t_gc GC_G = (t_gc) { .ref_count = 0 };

void	gc_init(void * ptr)
{
  if (GC_G.ref_count)
    GC_G.ref_count++;
  else
  {
    GC_G = (t_gc) {
      .stack_start = ptr,
      .pointer_map = { NULL },
      .pointer_nb = 0,
      .ref_count = 1
    };
  }
}

void	*gc_alloc(size_t size)
{
	void *ptr;

	if(!(ptr = malloc(size)))
		return (NULL);
	gc_list_push(&GC_G.pointer_map[HASH(ptr) % P_MAP_SIZE], (t_gc_ptr) {
		.start = (uintptr_t) ptr,
		.size = size
	});
	printf("ptr %llu\n", ptr);
	GC_G.pointer_nb++;
	return (ptr);
}

size_t	gc_ptr_index(uintptr_t ptr)
{
	int			i;
	int			j;
	t_gc_list	*e;

	i = -1;
	j = 0;
	while (++i < P_MAP_SIZE)
	{
		e = GC_G.pointer_map[i];
		while (e)
		{
			if (ptr >= e->data.start && e->data.start + e->data.size >= ptr)
				return (j);
			e = e->next;
			j++;
		}
	}
	return (-1);
}

void	gc_mark(uint8_t *mark_bits)
{
	uint8_t		*start;
	uint8_t		*end;
	size_t		index;

	start = GC_G.stack_start;
	end = (uint8_t *) STACK_PT;
	if (start > end) SWAP(uint8_t *, start, end)
	while (start < end)
	{
		index = gc_ptr_index((uintptr_t)*((void **)start));
		if (index != -1)
			SET_BIT(mark_bits, index, 1);
		start++;
	}
}
