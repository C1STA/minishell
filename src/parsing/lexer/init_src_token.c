/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_src_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 20:00:16 by imrane            #+#    #+#             */
/*   Updated: 2024/11/07 19:27:24 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_source	**init_src(t_source **src, char *input)
{
	t_source	*src_ft;

	*(src) = malloc(sizeof(t_source));
	src_ft = *src;
	src_ft -> buffer = input;
	src_ft -> bufsize = ft_strlen(input);
	src_ft -> curpos = 0;
	src_ft -> end_input = 0;
	src_ft -> exit = 0;
	return (src);
}

t_info_tok	**init_global_info_token(t_info_tok **info)
{
	t_info_tok	*info_ft;

	*(info) = malloc(sizeof(t_info_tok));
	info_ft = *(info);
	info_ft -> tok_buf = NULL;
	info_ft -> tok_bufsize = 0;
	info_ft -> tok_bufindex = -1;
	return (info);
}
