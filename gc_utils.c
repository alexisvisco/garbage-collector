/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gc_utils.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 13:12:10 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/10 15:51:14 by aviscogl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "gc.h"

t_gc_list	*gc_ptr_index(uintptr_t ptr)
{
	int			h;
	int			i;
	t_gc_list	*e;

	if (ptr > g_gc.max || ptr < g_gc.min)
	 	return (NULL);

	h = HASH(ptr) % P_MAP_SIZE;
	i = 0;

	if ((e = gc_ptr_list_search(ptr, g_gc.pointer_map[h])))
		return (e);
	while (++i + h < P_MAP_SIZE && i - h > 0)
	{
		if (!(h - i < 0)
			&& (e = gc_ptr_list_search(ptr, g_gc.pointer_map[h - i])))
			return (e);
		if (!(h + i >= P_MAP_SIZE)
			&& (e = gc_ptr_list_search(ptr, g_gc.pointer_map[h + i])))
			return (e);
	}
	return (NULL);
}

t_gc_list	*gc_ptr_list_search(uintptr_t ptr, t_gc_list *e)
{
	while (e)
	{
		if (ptr >= e->data.start
			&& e->data.start + e->data.size >= ptr)
			return (e);
		e = e->next;
	}
	return (NULL);
}

void	gc_mark_stack(void)
{
	uint8_t		tmp;
	t_gc_list	*e;

	gc_mark(g_gc.stack_start, &tmp);
	e = g_gc.globals;
	while (e)
	{
		gc_mark((uint8_t *)e->data.start,
				(uint8_t *)(e->data.start + e->data.size));
		e = e->next;
	}
}

void	swap_ptr(uint8_t **a, uint8_t **b)
{
	uint8_t *tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	debug_pointer_list(void)
{
	t_gc_list	*m;
	int			i;

	i = -1;
	printf("pointers lists:\n");
	while (++i < P_MAP_SIZE)
	{
		m = g_gc.pointer_map[i];
		if (m)
			printf(" - g_gc.pointer_map[%d]:\n", i);
		while (m)
		{
			printf("   { ptr: %p, size: %lu, marked: %d }\n",
			(void *)m->data.start, m->data.size, m->data.marked);
			m = m->next;
		}
	}
}
