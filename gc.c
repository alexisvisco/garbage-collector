#include "gc.h"

#define STACK_PT ({ char sp; &sp; })
#define HASH(ptr) ((uintptr_t)ptr >> 3)
#define SET_BIT(l, i, v) (l[i/8] |= 1 << (i % 8))
#define GET_BIT(l, i) ((l[i/8] >> (i % 8)) & 1)
#define SWAP(type, a, b) { type tmp; tmp = a; a = b; b = tmp; }

t_gc GC_G = (t_gc) { .ref_count = 0 };

void	gc_init(void * ptr, size_t limit)
{
  if (GC_G.ref_count)
    GC_G.ref_count++;
  else
  {
    GC_G = (t_gc) {
      .stack_start = ptr,
      .pointer_map = { NULL },
      .pointer_nb = 0,
      .ref_count = 1,
	  .limit = limit
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
	GC_G.pointer_nb++;
	if (GC_G.pointer_nb > GC_G.limit)
		gc_run();
	return (ptr);
}

void	gc_free(void *ptr)
{
	t_gc_list *lst;

	lst = GC_G.pointer_map[HASH(ptr) % P_MAP_SIZE];
	if (lst && gc_list_exist(lst, (uintptr_t)lst))
	{
		gc_list_rm(&lst, (uintptr_t)lst);
		GC_G.pointer_nb--;
		free(ptr);
	}
}

size_t	gc_ptr_index(uintptr_t ptr, t_gc_list **e)
{
	int			i;
	int			j;

	i = -1;
	j = 0;
	while (++i < P_MAP_SIZE)
	{
		*e = GC_G.pointer_map[i];
		while (*e)
		{
			if (ptr >= (*e)->data.start &&
			(*e)->data.start + (*e)->data.size >= ptr)
				return (j);
			*e = (*e)->next;
			j++;
		}
	}
	return (-1);
}

void	gc_mark_stack(uint8_t *mark_bits)
{
	gc_mark(mark_bits, GC_G.stack_start, (uint8_t *) STACK_PT);
}

void	gc_mark(uint8_t *mark_bits, uint8_t *start, uint8_t *end)
{
	size_t		index;
	t_gc_list	*e;

	if (start > end) SWAP(uint8_t *, start, end)
	while (start < end)
	{
		index = gc_ptr_index((uintptr_t)*((void **)start), &e);
		if (index != -1)
		{
			SET_BIT(mark_bits, index, 1);
			gc_mark(mark_bits, (uint8_t *)(e->data.start),
							(uint8_t *)(e->data.start + e->data.size));
		}
		start++;
	}
}

void	gc_sweep(uint8_t *mark_bits)
{
	int			i;
	int			j;
	int			k;
	t_gc_list	*e;

	i = -1;
	j = 0;
	while (++i < P_MAP_SIZE)
	{
		e = GC_G.pointer_map[i];
		k = 0;
		while (e)
		{
			if (GET_BIT(mark_bits, j) == 0)
			{
				free((void *)e->data.start);
				e = e->next;
				gc_list_rm(&GC_G.pointer_map[i], k);
				GC_G.pointer_nb--;
			}
			else
				e = e->next;
			j++;
			k++;
		}
	}
}

void 	gc_run()
{
	size_t	size;
	uint8_t	*mark_bits;

	size = (GC_G.pointer_nb / 8) + GC_G.pointer_nb % 8 != 0;
	mark_bits = alloca(size);
	while (size--)
		mark_bits[size] = 0;
	gc_mark_stack(mark_bits);
	gc_sweep(mark_bits);
}
