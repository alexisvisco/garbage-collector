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
#include <string.h>

#define IS_DEL(c, d) (c == d)

static int		count_words(char *s, char delimiter)
{
	int i;
	int words;

	i = -1;
	words = 0;
	while (s[++i])
		if (((i != 0 && IS_DEL(s[i], delimiter) &&
		!IS_DEL(s[i - 1], delimiter)) ||
		(s[i + 1] == '\0' && !IS_DEL(s[i], delimiter))))
			words++;
	return (words);
}

static char		*get_word(char *s, char delimiter)
{
	int		i;
	int		size;
	char	*word;

	i = -1;
	size = 0;
	while (s[++i] && !IS_DEL(s[i], delimiter))
		size++;
	word = GC_ALLOC(sizeof(char) * (size + 1));
	word[size] = '\0';
	while (*s && !IS_DEL(*s, delimiter))
	{
		*word++ = *s;
		s++;
	}
	return (word - size);
}

char			**ft_strsplit(char *s, char delimiter)
{
	int		size;
	char	**tab;
	char	*str;

	if (!s)
		return (NULL);
	size = count_words(s, delimiter);
	if (!(tab = GC_ALLOC((size + 1) * sizeof(char*))))
		return (NULL);
	tab[size] = 0;
	str = s;
	while (*str)
	{
		if (!IS_DEL(*str, delimiter))
		{
			*tab++ = get_word(str, delimiter);
			str += strlen(get_word(str, delimiter)) - 1;
		}
		str++;
	}
	return (tab - size);
}

int		main(int argc, char *argv[])
{
	gc_init(&argc, 1);

	char **test;

	//GC_REGISTER(global_test);
	test = ft_strsplit("helloj=world", '=');
	printf("%s\n", test[0]);
	printf("%s\n", test[1]);

	gc_run();

	debug_pointer_list();
	gc_destroy();
}
