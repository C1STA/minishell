/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 19:44:43 by imoumini          #+#    #+#             */
/*   Updated: 2022/06/15 19:44:46 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = ft_lstlast(*lst);
	if (!last)
	{
		*lst = new;
		return ;
	}
	last -> next = new;
}

// int	main(void)
// {
	// t_list *new;
	// int	*p = malloc(sizeof(int));
	// *p = 4;

	// t_list *old;
	// int	*q = malloc(sizeof(int));
	// *q = 3;
	// t_list *lst;
	// old = ft_lstnew(q);
	// new = ft_lstnew(p);
	//new = NULL;
	// lst = old;
	//  t_list * l =  NULL; 
	//  t_list * l2 =  NULL;
	//  ft_lstadd_back(&l, ft_lstnew((void*)1));
	//ft_lstadd_back(&lst, new);
	// int	*i;
	// while (lst != NULL)
	// {	
	// 	i = lst -> content;
	// 	printf("%i\n", *i);
	// 	lst = lst -> next;
	// }
	//ft_lstadd_back(&l, ft_lstnew((void*)1));
	// /* 1 */ check(l->content == (void*)1);
	// /* 2 */ check(l->next == 0);

	// ft_lstadd_back(&l, ft_lstnew((void*)2));
	// /* 3 */ check(l->content == (void*)1);
	// /* 4 */ check(l->next->content == (void*)2);
	// /* 5 */ check(l->next->next == 0);

	// ft_lstadd_back(&l2, ft_lstnew((void*)3));
	// ft_lstadd_back(&l2, ft_lstnew((void*)4));
	// ft_lstadd_back(&l, l2);
	// /* 6 */ check(l->content == (void*)1);
	// /* 7 */ check(l->next->content == (void*)2);
	// /* 8 */ check(l->next->next->content == (void*)3);
	// /* 9 */ check(l->next->next->next->content == (void*)4);
	// /* 10 */ check(l->next->next->next->next == 0);
// }