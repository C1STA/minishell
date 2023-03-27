/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 19:56:51 by imoumini          #+#    #+#             */
/*   Updated: 2022/06/18 19:56:53 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*tmp;
	t_list	*newlist;
	t_list	*new;

	tmp = lst;
	newlist = NULL;
	while (tmp != NULL)
	{
		new = ft_lstnew(f(tmp -> content));
		if (new == NULL)
		{
			ft_lstclear(&lst, del);
			return (NULL);
		}
		ft_lstadd_back(&newlist, new);
		tmp = tmp -> next;
	}
	return (newlist);
}
