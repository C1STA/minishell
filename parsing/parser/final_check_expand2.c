/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_check_expand2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:44:38 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/25 14:49:13 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_double_tab(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return ;
	while (str[i])
	{
		ft_printf("%s\n", str[i]);
		i++;
	}
}

int	double_tab_as_export(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		if (ft_stcmp(tab[i], "export") == 1)
			return (1);
		i++;
	}
	return (0);
}

void	final_expand(t_final *final)
{
	t_final	*follow;
	char	**save;

	if (!final)
		return ;
	follow = final;
	while (follow)
	{
		if (double_tab_as_export(follow -> cmds) == 0)
		{
			if (double_tab_as_space(follow -> cmds) == 1)
			{
				save = follow -> cmds;
				follow -> cmds = recreate_tab_without_space(follow -> cmds);
				free_double_tab(save);
			}
		}
		follow = follow->next;
	}
}

int	double_tab_as_space(char **tab)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		len = ft_strlen(tab[i]);
		while (j < len)
		{
			if (tab[i][j] == '-')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	tab_as_space(char *tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		if (tab[i] == '-' )
			return (1);
		i++;
	}
	return (0);
}
