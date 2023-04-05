/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/23 18:33:31 by imrane            #+#    #+#             */
/*   Updated: 2023/04/01 19:04:18 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void ft_exit(t_env **mini_env,t_node **root, t_source **src, t_info_tok **info)
{
    t_node *ptr;

    if (!root)
        return ;
    ptr = *root;
    if (ptr -> first_child == NULL)
        return ;
    ptr = ptr -> first_child;
    if ((ft_stcmp(ptr -> txt, "exit") == 1) && (ptr -> next_sibling == NULL))
	{
		ft_free(mini_env, root, src, info);
		exit (1);
	}
}
