/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_token5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 17:08:18 by imoumini          #+#    #+#             */
/*   Updated: 2024/11/07 19:27:24 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_single_quotes_str_closed(char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			count++;
		i++;
	}
	if (count % 2 == 0)
		return (1);
	return (0);
}

int	tokenize_quotes(t_source *src, t_info_tok *info, char c)
{
	if (c == '"' || c == '\'')
	{
		if (c == '"')
		{
			if (tokenize_double_quote(c, src, info) == 1)
				return (1);
		}
		else
		{
			if (tokenize_single_quote(c, src, info) == 1)
				return (1);
		}
	}
	return (0);
}
