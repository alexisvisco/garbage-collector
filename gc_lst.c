#include "gc.h"

int		gc_list_exist(t_gc_list *begin_list, uintptr_t ptr)
{
	while (begin_list)
	{
		if (begin_list->data.start == ptr)
			return (1);
		begin_list = begin_list->next;
	}
	return (0);
}

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

void		gc_list_rm(t_gc_list **begin_list, size_t index)
{
	t_gc_list	*node;
	t_gc_list	*prev;
	size_t		i;

	if ((node = *begin_list) == NULL)
		return ;
	prev = NULL;
	i = 0;
	while (node)
	{
		if (i == index)
		{
			if (prev)
				prev->next = node->next;
			else
				*begin_list = node->next;
			printf("something was remove !\n");
			free(node);
			return ;
		}
		prev = node;
		node = node->next;
		i++;
	}
}
