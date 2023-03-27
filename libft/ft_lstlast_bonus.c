/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/14 22:22:28 by imoumini          #+#    #+#             */
/*   Updated: 2022/06/14 22:22:33 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*tmp;

	if (lst == NULL)
	{
		return (NULL);
	}
	while (lst != NULL)
	{
		tmp = lst;
		lst = lst -> next;
	}
	return (tmp);
}

// int	main(void)
// {
// 	int *p = malloc(sizeof(int));
//     *p = 4;
// 	int *q = malloc(sizeof(int));
//     *q = 5;
// 	t_list *list;
//     t_list *n;
// 	t_list *o;
// 	t_list *z;
// 	n = ft_lstnew(p);
// 	o = ft_lstnew(q);
// 	n -> next = o;
// 	list = n;
// 	z = ft_lstlast(list);
// 	int *r = z -> content;
// 	printf("%d", *r );
// }
