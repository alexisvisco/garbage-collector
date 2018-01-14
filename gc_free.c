/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gc_free.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 13:28:22 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/10 13:38:28 by aviscogl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "gc.h"

void	gc_free(void *ptr)
{
	t_gc_list *lst;

	lst = g_gc.pointer_map[HASH(ptr) % P_MAP_SIZE];
	if (lst && gc_list_exist(lst, (uintptr_t)lst))
	{
		gc_list_rm(&lst, (uintptr_t)lst);
		gc_mfree(lst);
	}
}

void	gc_mfree(t_gc_list *e)
{
	DEBUGP("Free %p with size %zu allocated in %s:%d\n",
		(void *)e->data.start, e->data.size, e->data.file,
		e->data.line);
	free((void *)e->data.start);
	g_gc.pointer_nb--;
}
