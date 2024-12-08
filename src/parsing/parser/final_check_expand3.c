/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_check_expand3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/06 17:47:28 by imoumini          #+#    #+#             */
/*   Updated: 2024/12/08 22:52:24 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**tab_without_space(char *str, int nbr)
{
	char	**tab;
	int		begin;
	int		end;

	begin = 0;
	end = 0;
	tab = malloc(sizeof(char *) * (nbr + 1 + 1));
	tab[0] = NULL;
	tab = tab_without_space_while(str, begin, end, tab);
	return (tab);
}

char	**tab_without_space_while(char *str, int begin, int end, char **tab)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '-' )
		{
			begin = i;
			if (begin != end)
				tab[j++] = return_right_tab(str, begin, end);
			i++;
			while (str[i] && str[i] != '-')
				i++;
			end = i;
			if (begin != end)
				tab[j++] = return_right_tab(str, begin, end);
		}
		if (str[i] && str[i] != '-' )
			i++;
	}
	tab[j] = NULL;
	return (tab);
}

char	**recreate_while(char **tab, char **new_tab, int i, int j)
{
	char	**broken_tab;
	int		tab_i;

	while (tab[i])
	{
		if (tab_as_space(tab[i]) == 1)
		{
			tab_i = 0;
			broken_tab = tab_without_space(tab[i], nbr_space(tab[i]));
			while (broken_tab && broken_tab[tab_i])
			{
				new_tab[j] = ft_strdup(broken_tab[tab_i]);
				tab_i++;
				j++;
			}
			free_double_tab(broken_tab);
		}
		else
			new_tab[j] = ft_strdup(tab[i]);
		i++;
		j++;
	}
	new_tab[j - 1] = NULL;
	return (new_tab);
}

char	**recreate_tab_without_space(char **tab)
{
	char	**new_tab;
	int		i;
	int		count;
	int		j;

	i = 0;
	j = 0;
	count = 0;
	while (tab[i])
	{
		if (tab_as_space(tab[i]) == 1)
		{
			j--;
			count = nbr_space(tab[i]) + count;
		}
		i++;
		j++;
	}
	new_tab = malloc(sizeof(char *) *(count + 1 + j + 1));
	new_tab[1] = NULL;
	i = 0;
	j = 0;
	return (recreate_while(tab, new_tab, i, j));
}
