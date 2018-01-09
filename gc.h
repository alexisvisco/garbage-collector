#ifndef _GC_H_
# define _GC_H_

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>

# define P_MAP_SIZE 64

typedef struct  		s_gc_ptr {
  uintptr_t          	start;
  size_t				size;
}               		t_gc_ptr;

typedef struct			s_gc_list
{
	struct s_gc_list	*next;
	t_gc_ptr			data;
}						t_gc_list;

typedef struct  		s_gc {
  void          		*stack_start;
  t_gc_list     		*pointer_map[P_MAP_SIZE];
  size_t				pointer_nb;
  size_t				ref_count;
}               		t_gc;

extern t_gc GC_G;

void					gc_init(void *ptr);
void					*gc_alloc(size_t size);
void					gc_mark(uint8_t *mark_bits);
size_t					gc_ptr_index(uintptr_t ptr);


void					gc_list_push(t_gc_list **begin_list, t_gc_ptr data);
int						gc_list_size(t_gc_list *begin_list);
t_gc_list				*gc_list_at(t_gc_list *begin_list, size_t nbr);


#endif
