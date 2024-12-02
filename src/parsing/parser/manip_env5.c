/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dpinto <dpinto@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:38:31 by imoumini          #+#    #+#             */
/*   Updated: 2024/11/24 03:48:11 by dpinto           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_job_multiple_dollar(t_node *ptr, int nbr)
{
	int		i;
	char	*str_nbr;
	char	*save_before_dollar;
	char	*save_after_dollar;
	char	*new_str;

	i = 0;
	while (ptr->txt[i] != '\0')
	{
		if (expand_guillemets(ptr->txt, i) == 1)
		{
			if (ptr->txt[i] == '$')
			{
				save_before_dollar = before_dollar(ptr->txt);
				str_nbr = add_nbr(nbr);
				save_after_dollar = after_multiple_dollar(ptr->txt, nbr);
				new_str = ft_strjoin(save_before_dollar, str_nbr);
				new_str = ft_strjoin(new_str, save_after_dollar);
				free_expand_job_mutiple(str_nbr, save_after_dollar, ptr->txt);
				ptr->txt = new_str;
				return ;
			}
		}
		i++;
	}
}

void	free_elem(void **elem)
{
	if (*elem == NULL)
		return ;
	free(*elem);
}

void	expand_job(t_env *head, t_node *ptr)
{
	int		i;
	char	*save_var;
	char	*b_do;
	char	*a_do;
	char	*str;

	i = -1;
	a_do = ft_strdup("a");
	while (ptr->txt && ptr->txt[++i] != '\0')
	{
		if (ptr->txt[i] == '$' && expand_guillemets(ptr->txt, i) == 1)
		{
			free(a_do);
			b_do = before_dollar(ptr->txt);
			save_var = catch_var(ptr->txt + (i + 1));
			a_do = after_dollar_deux(find_end_of_var(ptr->txt + (i + 1)));
			str = ft_strjoin(b_do, return_matching_value(head, save_var));
			final_txt(a_do, str, ptr, save_var);
			a_do = NULL;
			free(b_do);
			b_do = NULL;
		}
	}
	free_elem((void **)&a_do);
}

int	more_than_one_dollars_suite(t_node *ptr)
{
	int	i;

	i = 0;
	while (ptr->txt[i])
	{
		if (ptr->txt[i] == '$')
		{
			if (ptr->txt[i + 1])
			{
				if (ptr->txt[i + 1] == '$' && ptr->txt[i + 2])
					return (1);
			}
		}
		i++;
	}
	return (0);
}

char	*after_multiple_dollar(char *str, int nbr)
{
	int	i;
	int	save;

	i = 0;
	save = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] && str[i + 1] == '$')
		{
			after_multiple_dollar_while(nbr, &i, &save);
			break ;
		}
		i++;
	}
	return (return_after_multiple_dollar(str, i, save));
}
