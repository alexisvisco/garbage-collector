/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gc_core.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 10:28:35 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/10 14:26:42 by aviscogl    ###    #+. /#+    ###.fr     */
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
		g_gc = (t_gc) {
			.stack_start = ptr,
			.pointer_map = { NULL },
			.pointer_nb = 0,
			.ref_count = 1,
			.limit = limit
		};
	}
}

void	gc_mark(uint8_t *mark_bits, uint8_t *start, uint8_t *end)
{
	size_t		index;
	t_gc_list	*e;

	if (start > end)
		swap_ptr(start, end);
	while (start < end)
	{
		index = gc_ptr_index((uintptr_t)(*((void **)start)), &e);
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
		e = g_gc.pointer_map[i];
		k = 0;
		while (e)
		{
			if (GET_BIT(mark_bits, j) == 0)
			{
				free((void *)e->data.start);
				e = e->next;
				gc_list_rm(&g_gc.pointer_map[i], k);
				g_gc.pointer_nb--;
			}
			else
				e = e->next;
			j++;
			k++;
		}
	}
}

void	gc_run(void)
{
	size_t	size;
	uint8_t	*mark_bits;

	size = (g_gc.pointer_nb / 8) + g_gc.pointer_nb % 8 != 0;
	mark_bits = alloca(size);
	while (size--)
		mark_bits[size] = 0;
	gc_mark_stack(mark_bits);
	gc_sweep(mark_bits);
}

void	gc_destroy(void)
{
	int			i;
	t_gc_list	**m;
	t_gc_list	*tmp;

	i = -1;
	g_gc.ref_count--;
	if (g_gc.ref_count <= 0)
	{
		g_gc.ref_count = 0;
		while (++i < P_MAP_SIZE)
		{
			*m = &g_gc.pointer_map[i];
			while (*m)
			{
				tmp = *m;
				free((void *)((*m)->data.start));
				m = tmp->next;
				free(tmp);
			}
		}
	}
}
