/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:38:31 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/25 12:06:14 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	expand_job_multiple_dollar(t_node *ptr, int nbr)
{
	int		i;
	char	*str_nbr;
	char	*save_before_dollar;
	char	*save_after_dollar;
	char	*new_str;

	i = 0;
	while (ptr -> txt[i] != '\0')
	{
		if (expand_guillemets(ptr -> txt, i) == 1)
		{
			if (ptr ->txt[i] == '$')
			{
				save_before_dollar = before_dollar(ptr -> txt);
				str_nbr = add_nbr(nbr);
				save_after_dollar = after_multiple_dollar(ptr -> txt, nbr);
				new_str = ft_strjoin(save_before_dollar, str_nbr);
				new_str = ft_strjoin(new_str, save_after_dollar);
				free_expand_job_mutiple(str_nbr, save_after_dollar, ptr->txt);
				ptr -> txt = new_str;
				return ;
			}
		}
		i++;
	}
}

void	expand_job(t_env *head, t_node *ptr)
{
	int		i;
	char	*save_var;
	char	*b_do;
	char	*a_do;
	char	*str;

	i = 0;
	a_do = NULL;
	a_do = init_save_after_dollar(a_do);
	while (ptr -> txt[i] != '\0')
	{
		if (ptr ->txt[i] == '$')
		{
			if (expand_guillemets(ptr -> txt, i) == 1)
			{
				free(a_do);
				b_do = before_dollar(ptr -> txt);
				save_var = catch_var(ptr->txt + (i + 1));
				a_do = after_dollar_deux(find_end_of_var(ptr->txt + (i + 1)));
				str = ft_strjoin(b_do, return_matching_value(head, save_var));
				final_txt(a_do, str, ptr, save_var);
			}
		}
		i++;
	}
}

int	more_than_one_dollars_suite(t_node *ptr)
{
	int	i;

	i = 0;
	while (ptr -> txt[i])
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
