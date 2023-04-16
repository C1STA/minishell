/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env11.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 18:20:50 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/15 18:40:22 by imoumini         ###   ########.fr       */
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
