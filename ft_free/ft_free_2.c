/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 15:36:23 by wcista            #+#    #+#             */
/*   Updated: 2023/04/25 15:40:38 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_info(t_info_tok **info)
{
	t_info_tok	*ptr;

	if (info)
	{
		ptr = *info;
		if (ptr)
		{
			if (ptr -> tok_buf)
			{
				free(ptr -> tok_buf);
				ptr -> tok_buf = NULL;
			}
			free(ptr);
			ptr = NULL;
		}
		else
			free(ptr);
		info = NULL;
	}
}

void	free_src(t_source **src)
{
	t_source	*ptr;

	if (src)
	{
		ptr = *src;
		if (ptr)
		{
			if (ptr -> buffer)
			{
				free (ptr -> buffer);
				ptr -> buffer = NULL;
			}
			free(ptr);
		}
		src = NULL;
	}
}

void	free_tok(t_token **tok)
{
	t_token	*ptr;

	if (tok)
	{
		ptr = *tok;
		if (ptr)
		{
			if (ptr -> text)
			{
				if (ptr -> text)
				{
					free(ptr-> text);
					ptr -> text = NULL;
				}
				ptr -> text = NULL;
			}
			free(ptr);
		}
		tok = NULL;
	}
}

void	free_info_buf(t_info_tok *info)
{
	t_info_tok	*ptr;

	if (info)
	{
		ptr = info;
		if (ptr)
		{
			if (ptr -> tok_buf)
			{
				free(ptr -> tok_buf);
				ptr -> tok_buf = NULL;
			}
			ptr -> tok_buf = NULL;
		}
	}
}

void	free_expand_job_mutiple(char *str_nbr, char *dollar, char *txt)
{
	free(dollar);
	free(txt);
	free (str_nbr);
}
