/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env11.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:20:50 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/22 20:54:54 by imoumini         ###   ########.fr       */
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
