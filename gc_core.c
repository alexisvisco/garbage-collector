/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gc_core.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 10:28:35 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/10 15:54:56 by aviscogl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "gc.h"

t_gc g_gc = (t_gc) { .ref_count = 0 };

void	gc_init(void *ptr, size_t limit)
{
	if (g_gc.ref_count)
		g_gc.ref_count++;
	else
	{
		DEBUGP("Init\n");
		g_gc = (t_gc) {
			.stack_start = ptr,
			.pointer_map = { NULL },
			.pointer_nb = 0,
			.ref_count = 1,
			.limit = limit,
			.min = UINTPTR_MAX,
			.max = 0,
			.globals = NULL
		};
	}
}

void	gc_mark(uint8_t *start, uint8_t *end)
{
	t_gc_list	*index;

	if (start > end)
		swap_ptr(&start, &end);
	while (start < end)
	{
		index = gc_ptr_index((uintptr_t)(*((void **)start)));
		if (index && index->data.marked != true)
		{
			index->data.marked = true;
			gc_mark((uint8_t *)(index->data.start),
					(uint8_t *)(index->data.start + index->data.size));
		}
		start++;
	}
}

void	gc_sweep(void)
{
	int			i;
	int         k;
	t_gc_list	*e;

	i = 0;
	while (++i < P_MAP_SIZE)
	{
		e = g_gc.pointer_map[i];
		k = 0;
		while (e)
		{
			if (!e->data.marked)
			{
				gc_mfree(e);
				e = e->next;
				gc_list_rm(&g_gc.pointer_map[i], k);
			}
			else
			{
				e->data.marked = false;
				e = e->next;
			}
			k++;
		}
	}
}

void	gc_run(void)
{
	DEBUGP("Running\n");
	gc_mark_stack();
	gc_sweep();
}

void	gc_destroy(void)
{
	int			i;
	t_gc_list	*m;
	t_gc_list	*tmp;

	i = -1;
	g_gc.ref_count--;
	if (g_gc.ref_count <= 0)
	{
		g_gc.ref_count = 0;
		while (++i < P_MAP_SIZE)
		{
			m = g_gc.pointer_map[i];
			while (m)
			{
				tmp = m;
				free((void *)(m->data.start));
				m = m->next;
				free(tmp);
			}
			g_gc.pointer_map[i] = 0;
		}
	}
}
