/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env11.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:20:50 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/25 21:42:09 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand_guillemets_first(char *s, int *i_dol, int *nb_simp, int *i_simp)
{
	while (*(i_dol) >= 0)
	{
		if (s[*(i_dol)] == '\'')
		{
			*(nb_simp) = *(nb_simp) + 1;
			*(i_simp) = *(i_dol);
		}
		*(i_dol) = *(i_dol) - 1;
	}
}

void	if_double_env(char *new_str, int *i, int *j, char *str)
{
	if (str[*(i)] == '"')
	{
		*(i) = *(i) + 1;
		if (str[*(i)])
			return ;
		while (str[*(i)])
		{
			if (str[*(i)] == '"')
			{
				*(i) = *(i) + 1;
				break ;
			}
			new_str[*(j)] = str[*(i)];
			*(j) = *(j) + 1;
			*(i) = *(i) + 1;
		}
	}
}

void	if_simple_env(char *new_str, int *i, int *j, char *str)
{
	if (str[*(i)] == '\'')
	{
		*(i) = *(i) + 1;
		if (str[*(i)])
			return ;
		while (str[*(i)])
		{
			if (str[*(i)] == '\'')
			{
				*(i) = *(i) + 1;
				break ;
			}
			new_str[*(j)] = str[*(i)];
			*(j) = *(j) + 1;
			*(i) = *(i) + 1;
		}
	}
}

char	*add_nbr(int nbr)
{
	char	*str_nbr;
	int		count;

	count = 2;
	while (nbr > 1)
	{
		if (count == 2)
		{
			str_nbr = malloc(sizeof(char) * 8);
			init_str_nbr(str_nbr);
			count--;
			if (nbr == 2)
				return (str_nbr);
		}
		if (count == 0)
			str_nbr = ft_strjoin(str_nbr, str_nbr);
		if (count >= 0)
			count--;
		if (nbr > 0)
			nbr = nbr / 2;
	}
	return (str_nbr);
}
