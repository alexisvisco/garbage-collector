/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gc.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 13:16:08 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/10 15:36:39 by aviscogl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef GC_H
# define GC_H

# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <stdbool.h>
# include <limits.h>
# include <alloca.h>

# define P_MAP_SIZE 64
# define HASH(ptr) ((uintptr_t)ptr >> 3)
# define GC_ALLOC(x) gc_alloc(x, __FILE__, __LINE__)
# define GC_FREE(x) gc_free(x)
# define GC_REGISTER(x) gc_register(&x, sizeof(x), __FILE__, __LINE__)

# ifdef DEBUG
#  define DEBUGP(...) printf("GC: " __VA_ARGS__)
# else
#  define DEBUGP(...)
# endif

typedef struct			s_gc_ptr
{
	uintptr_t			start;
	size_t				size;
	bool 				marked;
# ifdef DEBUG
	char				*file;
	int					line;
# endif
}						t_gc_ptr;

typedef struct			s_gc_list
{
	struct s_gc_list	*next;
	t_gc_ptr			data;
}						t_gc_list;

typedef struct			s_gc
{
	void				*stack_start;
	t_gc_list			*pointer_map[P_MAP_SIZE];
	size_t				pointer_nb;
	size_t				limit;
	size_t				ref_count;
	uintptr_t			min;
	uintptr_t			max;
	t_gc_list			*globals;
}						t_gc;

extern t_gc g_gc;

void					gc_init(void *ptr, size_t limit);
void					*gc_alloc(size_t size, char *file, int line);
void					gc_free(void *ptr);
void					gc_mfree(t_gc_list *e);
void					gc_mark(uint8_t *s, uint8_t *e);
void					gc_register(void *ptr, size_t size, char *f, int l);
t_gc_list				*gc_ptr_index(uintptr_t ptr);
t_gc_list				*gc_ptr_list_search(uintptr_t ptr, t_gc_list *e);
void					gc_run();
void					gc_sweep();
void					gc_destroy(void);
void					gc_mark_stack(void);

void					swap_ptr(uint8_t **a, uint8_t **b);
void					debug_pointer_list(void);

void					gc_list_push(t_gc_list **begin_list, t_gc_ptr data);
void					gc_list_rm(t_gc_list **begin_list, size_t index);
int						gc_list_exist(t_gc_list *begin_list, uintptr_t ptr);

#endif
