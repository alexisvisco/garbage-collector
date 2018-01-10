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
# include <alloca.h>

# define P_MAP_SIZE 64
# define STACK_PT ({ char sp; &sp; })
# define HASH(ptr) ((uintptr_t)ptr >> 3)
# define SET_BIT(l, i, v) (l[i/8] |= 1 << (i % 8))
# define GET_BIT(l, i) ((l[i/8] >> (i % 8)) & 1)

typedef struct			s_gc_ptr
{
	uintptr_t			start;
	size_t				size;
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
}						t_gc;

extern t_gc g_gc;

void					gc_init(void *ptr, size_t limit);
void					*gc_alloc(size_t size);
void					gc_mark(uint8_t *mark_bits, uint8_t *s, uint8_t *e);
size_t					gc_ptr_index(uintptr_t ptr, t_gc_list **e);
void					gc_mark_stack(uint8_t *mark_bits);
void					gc_run();
void					gc_sweep(uint8_t *mark_bits);
void					gc_free(void *ptr);
void					gc_destroy(void);

void					swap_ptr(uint8_t *a, uint8_t *b);
void					debug_pointer_list(void);

void					gc_list_push(t_gc_list **begin_list, t_gc_ptr data);
void					gc_list_rm(t_gc_list **begin_list, size_t index);
int						gc_list_exist(t_gc_list *begin_list, uintptr_t ptr);

#endif
