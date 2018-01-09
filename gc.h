#ifndef _GC_H_
# define _GC_H_

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <alloca.h>

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
  size_t				limit;
  size_t				ref_count;
}               		t_gc;

extern t_gc GC_G;

void					gc_init(void * ptr, size_t limit);
void					*gc_alloc(size_t size);
void					gc_mark(uint8_t *mark_bits, uint8_t *s, uint8_t *e);
size_t					gc_ptr_index(uintptr_t ptr, t_gc_list **e);
void					gc_mark_stack(uint8_t *mark_bits);
void					gc_run();
void					gc_sweep(uint8_t *mark_bits);
void					gc_free(void *ptr);


void					gc_list_push(t_gc_list **begin_list, t_gc_ptr data);
void					gc_list_rm(t_gc_list **begin_list, size_t index);
int						gc_list_exist(t_gc_list *begin_list, uintptr_t ptr);


#endif
