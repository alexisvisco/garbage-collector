/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gc_alloc.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 13:27:33 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/10 13:48:58 by aviscogl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "gc.h"

void	*gc_alloc(size_t size)
{
	void		*ptr;
	t_gc_ptr	p;

	if (!(ptr = malloc(size)))
		return (NULL);
	p = (t_gc_ptr) {
		.start = (uintptr_t)ptr,
		.size = size
	};
	gc_list_push(&g_gc.pointer_map[HASH(ptr) % P_MAP_SIZE], p);
	g_gc.pointer_nb++;
	if (g_gc.pointer_nb > g_gc.limit)
		gc_run();
	return (ptr);
}
