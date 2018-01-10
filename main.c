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

	gc_init(&argc, 1);

	sample(&h);
	gc_alloc(1);
	
	gc_destroy();
}
