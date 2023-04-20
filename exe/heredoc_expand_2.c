/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 10:43:18 by wcista            #+#    #+#             */
/*   Updated: 2023/04/20 02:33:51 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

static void	get_from_env(t_heredoc *h, char *env[])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (env[i])
	{
		if ((int)ft_strlen(h->tmp) == env_var_len(env[i]))
		{
			if (!ft_strncmp(env[i], h->tmp, env_var_len(env[i])))
			{
				j = ft_strlen(h->tmp) + 1;
				while (env[i][j])
				{
					h->dest[h->k] = env[i][j];
					j++;
					h->k++;
				}
				break ;
			}
		}
		i++;
	}
	if (h->input[h->i] == '$')
		h->dollar = true;
	free(h->tmp);
}

static void	get_tmp(t_heredoc *h, char *env[])
{
	int	k;

	h->tmp = (char *)malloc(sizeof(char) * h->j + 1);
	if (!h->tmp)
		return (print_perror("malloc"));
	k = 0;
	while (k < h->j)
	{
		h->tmp[k] = h->input[h->i_save];
		h->i_save++;
		k++;
	}
	h->tmp[k] = '\0';
	printf("tmp ===  ____%s____\n", h->tmp);
	get_from_env(h, env);
}

char	*heredoc_expanded(t_heredoc *h, char *env[])
{
	h->i = 0;
	h->k = 0;
	h->dollar = false;
	h->dest = (char *)malloc(sizeof(char) * h->len + 1);
	if (!h->dest)
		return (h->input);
	while (h->input[h->i])
	{
		h->j = 0;
		if (h->input[h->i] == '$' && h->input[h->i + 1] && h->input[h->i + 1] \
	!= '$' && ft_isalnum(h->input[h->i + 1]))
		{
			h->i++;
			h->i_save = h->i;
			if (ft_isalpha(h->input[h->i]))
			{
				while (h->input[h->i] && h->input[h->i] != '$' \
				&& ft_isalnum(h->input[h->i]))
				{
					h->i++;
					h->j++;
				}
				get_tmp(h, env);
			}
			else
				h->i++;
		}
		else if (h->dollar == true)
			h->dollar = false;
		else
		{
			h->dest[h->k] = h->input[h->i];
			h->i++;
			h->k++;
		}
	}
	h->dest[h->k] = '\0';
	printf("dest=__%s__\n", h->dest);
	free(h->input);
	return (h->dest);
}
