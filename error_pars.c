/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:50:27 by imrane            #+#    #+#             */
/*   Updated: 2023/04/01 18:45:17 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int error_pars(t_node *head)
{
    if (!head)
    {
		return(2);
	}
    if (ft_in_file(head) == 0)
    {
		return(0);
	}
	if (ft_pipe_check(head) == 0)
    {
		return(0);
	}
	// remplacer par une fonction export qui tema tout, 
	// attention normalement je suis senser une var apres expand
	// du coup export doi avoir leiu apres le expand
	if (quote_closed(head) == 0)
	{
		return (0);
	}
    return (1);
}

int check_space_append_heredoc(char *str)
{
	int i;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i +1])
			{
				if (str[i + 1] == ' ' || str[i+1] == '\t')
				{
					i++;
					while (str[i] == ' ' || str[i] == '\t')
						i++;
					if (str[i] == '>' || str[i] == '<')
					{
						ft_printf("parse error near '%c'\n", str[i]);
						return (0);
					}
				}
			}
		}
		i++;
	}
	return (1);
}