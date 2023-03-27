/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/18 18:53:05 by imoumini          #+#    #+#             */
/*   Updated: 2022/06/18 18:53:08 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	while (lst != NULL)
	{
		f(lst -> content);
		lst = lst -> next;
	}
}

// void    plus(void * lst)
// {
//     int *p;
//     p = ((t_list *)lst) -> content;
//     *p = *p + 1;
// }
// int	main(void)
// {
// 	int *p = malloc(sizeof(int));
//     *p = 4;
// 	int *q = malloc(sizeof(int));
//     *q = 5;
// 	t_list *list;
//     t_list *n;
// 	t_list *o;
// 	// t_list *z;

// 	n = ft_lstnew(p);
// 	o = ft_lstnew(q);
// 	n -> next = o;
// 	list = n;
//     ft_lstiter(list, plus);
//     t_list *tmp;
//     tmp = list;
// 	while (tmp != NULL)
//     {
//         int *s;
//         s = tmp -> content;
//         printf("%d", *s);
//         tmp = tmp -> next;
//     }
// 	z = ft_lstlast(list);
// 	int *r = z -> content;
// 	printf("%d", *r );
// }
