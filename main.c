/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aviscogl <aviscogl@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/01/10 13:33:17 by aviscogl     #+#   ##    ##    #+#       */
/*   Updated: 2018/01/10 16:03:20 by aviscogl    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "gc.h"

#define malloc(x) gc_alloc(x)
#define free(x)

void	sample(void **h)
{
	void **hello;
	void *hi;

	hello = gc_alloc(10);
	*hello = gc_alloc(11);
	*hello += 3;
	*h = *hello;
}

int		main(int argc, char *argv[])
{
	void *h;
	int *e;

	gc_init(&argc, 1);

	sample(&h);
	debug_pointer_list();
	printf("-------\n");
	h = NULL;
	e = gc_alloc(1);
	*e = 17;
	debug_pointer_list();
	printf("%d\n", *e);
	gc_destroy();
}
