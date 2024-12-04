/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_pars.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 20:50:27 by imrane            #+#    #+#             */
/*   Updated: 2024/12/04 17:53:45 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	print_error_syntax_c(char c)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	g_exit_status = 2;
}

int	error_pars(t_node *head)
{
	if (!head)
		return (2);
	if (ft_in_file(head) == 0)
		return (0);
	if (ft_pipe_check(head) == 0)
		return (0);
	return (1);
}

int	check_space_append_heredoc(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i +1])
			{
				if (str[i + 1] == ' ' || str[i + 1] == '\t')
				{
					i++;
					while (str[i] == ' ' || str[i] == '\t')
						i++;
					if (str[i] == '>' || str[i] == '<')
						return (print_error_syntax_c(str[i]), 0);
				}
			}
		}
		i++;
	}
	return (1);
}

int	does_quotes_closed(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (!(str[i]))
				return (print_error_quotes("quotes"), 0);
		}
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			if (!(str[i]))
				return (print_error_quotes("quotes"), 0);
		}
		i++;
	}
	return (1);
}
