/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 23:17:22 by imoumini          #+#    #+#             */
/*   Updated: 2022/06/15 23:17:25 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list		*tmp;

	while (*lst != NULL)
	{
		tmp = (*lst)-> next;
		ft_lstdelone(*lst, del);
		*lst = tmp;
	}
}

// 	z = ft_lstlast(list);
// 	int *r = z -> content;
// 	ft_lstclear(&list, &del);
// 	printf("%p", list );
// }

// void ft_lstclear(t_list **lst, void (*del)(void*))
// {
//     t_list    *lastnode;
//     t_list    *beforelastnode; 
//     int nbr;
//     int i;
//     i = 0;
//     if (*lst == NULL)
//     {
//         return;
//     }
//     while (i <= ft_lstsize(*lst) /*- 1*/)
//     {
//         nbr = ft_lstsize(*lst);
//         lastnode = ft_lstlast(*lst);
//         beforelastnode = ft_lstbeforelast(*lst);
//         if (beforelastnode -> next != NULL)
//         {
//           beforelastnode -> next = NULL;
//         }
//         del(lastnode -> content);
//         free(lastnode);
//         if (nbr == i)
//          {
//            *lst = NULL;
// 		   free(*lst); 
//          }
//         i++;
//     }                                                                        
// }

// t_list *ft_lstbeforelast(t_list *lst)
// {
//     int	i;
// 	int	l;

// 	i = 0;
// 	l = ft_lstsize(lst);
// 	while (i < l - 2)
//	{
//	i++;
// 		lst = lst -> next;
// 	}
// 	return (lst);
// }
// void del(void* bob)
// {
// 	if (bob != NULL)
// 	{
// 		bob = NULL;
// 	}
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
// 	t_list *z;

// 	n = ft_lstnew(p);
// 	o = ft_lstnew(q);
// 	n -> next = o;
// 	list = n;