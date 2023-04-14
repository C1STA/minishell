/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:53:36 by wcista            #+#    #+#             */
/*   Updated: 2023/04/13 17:38:23 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_exe.h"
#include <readline/readline.h>
#include <readline/history.h>



char	*allocate_new_line(char *s, char *env[])
{
	int		i;
	int		j;
	int		res;
	char	*dest;

	i = 0;
	(void)env;
	while (s[i])
	{
		j = 0;
		if (s[i] == '$')
		{
			while (isalnum(s[i] || s[i] == '_'))
			{
				j++;
				i++;
			}
			res = res + get_bytes_from_env(s, env, i, j);
		}
		i++;
	}
}

int	main(int ac, char *av[], char *env[])
{
	char	*s;
	(void)env;
	if (ac < 2)
	s = readline("> ");
	if (!strcmp(s, av[1]))
		return (printf("EOF\n"), 0);
	
}