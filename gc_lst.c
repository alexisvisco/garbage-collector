#include "gc.h"

void	gc_list_push(t_gc_list **begin_list, t_gc_ptr data)
{
	t_gc_list *elem;

	if (begin_list == 0)
		return ;
	elem = malloc(sizeof(t_gc_list));
	*elem = (t_gc_list) {
		.data = data,
		.next = *begin_list
	};
	*begin_list = elem;
}

int		gc_list_size(t_gc_list *begin_list)
{
	size_t i;

	if (!begin_list)
		return (0);
	i = 1;
	while ((begin_list = begin_list->next))
		i++;
	return (i);
}

t_gc_list	*gc_list_at(t_gc_list *begin_list, size_t nbr)
{
	if (nbr == 0)
		return (begin_list);
	while (--nbr && begin_list && begin_list->next)
		begin_list = begin_list->next;
	return (nbr ? 0 : begin_list->next);
}
