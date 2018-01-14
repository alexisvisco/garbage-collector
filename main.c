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

char *global_test;

int		main(int argc, char *argv[])
{
	gc_init(&argc, 1);

	GC_REGISTER(global_test);
	global_test = GC_ALLOC(sizeof(char) * 10);
	global_test[0] = 'a';
	global_test[1] = 'b';
	global_test[2] = 'c';
	global_test[3] = '\0';
	global_test = NULL;

	gc_run();
	gc_run();

	printf("global_test = %s\n", global_test);
	debug_pointer_list();
	gc_destroy();
}
