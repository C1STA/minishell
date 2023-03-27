/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 21:53:11 by imoumini          #+#    #+#             */
/*   Updated: 2022/06/13 21:53:13 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>

t_list	*ft_lstnew(void *content)
{
	t_list	*n;

	n = malloc(sizeof(t_list));
	if (n == NULL)
	{
		return (NULL);
	}
	n -> content = content;
	n -> next = NULL;
	return (n);
}

// int main(void)
// {
// 	int tab[] = {0, 1, 2, 3};
// 	t_list * l =  ft_lstnew(tab);
// 	t_list *tmp;
// 	t_list *list;
// 	list = l;
//     tmp = list;
// 	int i;
// 	i = 0;
// 	while (tmp != NULL)
//     {
//         int *s;
//         s = tmp -> content;
// 		while (i < 4)
//         {
// 			printf("%d", s[i]);
// 			i++;
// 		}
//         tmp = tmp -> next;
//     }
// }
