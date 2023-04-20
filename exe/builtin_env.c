/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 14:05:45 by wcista            #+#    #+#             */
/*   Updated: 2023/04/20 14:06:02 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

extern int	g_exit_status;

bool	builtin_env(char *env[], t_pipex *p)
{
	int	i;

	i = 0;
	if (!env)
		return (true);
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
	p->exit_status = 0;
	return (true);
}
