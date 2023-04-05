/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_check_expand.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 14:48:42 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/02 18:51:56 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void print_double_tab(char **str)
{
	int i;

	i = 0;
	if (!str)
	{
		ft_printf("double tab is empty\n");
		return ;
	}
	ft_printf("double tab is \n");
	while (str[i])
	{
		ft_printf("%s\n", str[i]);
		i++;
	}
	
}

int double_tab_as_export(char **tab)
{
	int i;

	i = 0;
	printf("c6.3.1\n");
	if (!tab)
		return (0);
	printf("c6.3.2\n");
	while (tab[i])
	{
		printf("c6.3.3\n");
		printf("tab de i is=>%s\n", tab[i]);
		// ok je crois que je mets jamais NULL dans le cas de USER sans env
		if (ft_stcmp(tab[i], "export") == 1)
			return (1);
		printf("c6.3.4\n");
		i++;
	}
	
	return (0);
}
void final_expand(t_final *final)
{
	t_final *follow;
	char **save;

	printf("c6.1\n");
	if (!final)
		return ;
	follow = final;
	printf("c6.2\n");
	while (follow)
	{
		printf("c6.3\n");
		if (double_tab_as_export(follow -> cmds) == 0)
		{
			printf("c6.4\n");
			if (double_tab_as_space(follow -> cmds) == 1)
			{
				printf("c6.5\n");
				save = follow -> cmds;
				printf("c6.6\n");
				follow -> cmds = recreate_tab_without_space(follow -> cmds);
				printf("c6.7\n");
				print_double_tab(follow -> cmds);
				printf("c6.8\n");
				free_double_tab(save);
				printf("c6.9\n");
			}	
		}
		follow = follow -> next_sibling;
		printf("c6.10\n");
	}
}

int double_tab_as_space(char **tab)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!tab)
		return (0);
	while (tab[i])
	{
		while(tab[i][j])
		{
			if (tab[i][j] == ' ' || tab[i][j] == '\t' || tab[i][j] == '-' )
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int tab_as_space(char *tab)
{
	int i;
	i = 0;
	
	while (tab[i])
	{
		if (tab[i] == ' ' || tab[i] == '\t' || tab[i] == '-' )
				return (1);
		i++;
	}
	return (0);
}


void free_double_tab(char **str)
{
	int i;



	i = 0;
	
	if (!str)
		return ;
	while (str[i])
	{
		if (str[i])
		{
			free(str[i]);
			str[i] = NULL;
		}
		i++;
	}
	free(str);
}
int nbr_space(char *str)
{
	int i;
	int count;

	count = 0;
	i = 0;

	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '-' )
			count++;
		i++;
	}
	return (count);
}

char *return_right_tab(char *str, int begin, int end)
{
	char *tab;
	int i;
	i = 0;

	if (begin > end)
	{
		tab = malloc(sizeof(char) * (((begin - 1)- end) + 1));
		while (begin > end)
		{
			if (str[end])
				tab[i] = str[end];
			i++;
			end++;
		}
	}
	else if (begin < end)
	{
		tab = malloc(sizeof(char) * ((end - begin) + 1));
		while (end > begin)
		{
			if (str[begin])
				tab[i] = str[begin];
			i++;
			begin++;
		}
	}
	else
		return (NULL);
	tab[i] = '\0';
	return (tab);
}

char **tab_without_space(char *str, int nbr)
{
	char **tab;
	int begin;
	int end;
	int i;
	int j;

	i = 0;
	j = 0;
	end = 0;
	tab = malloc(sizeof(char *) * (nbr + 1 + 1));
	while (str[i] != '\0')
	{
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '-' )
		{
			begin = i;
			if(begin != end)
			{
				tab[j] = return_right_tab(str, begin, end);
				j++;
			}
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '-')
				i++;
			end = i;
			if(begin != end)
			{
				tab[j] = return_right_tab(str, begin, end);
				j++;
			}
		}
		if (str[i] && str[i] != ' ' && str[i] != '\t' && str[i] != '-' )
			i++;
	}
	tab[j] = NULL;
	return (tab);
}
char **recreate_tab_without_space(char **tab)
{
	int i;
	int count;
	int tab_i;
	int j;
	char **new_tab;
	char **broken_tab;
	
	i = 0;
	j = 0;
	count = 0;
	while (tab[i])
	{
		if(tab_as_space(tab[i]) == 1)
		{
			j--;
			count = nbr_space(tab[i]) + count;
		}
		i++;
		j++;
	}
	new_tab = malloc(sizeof(char *) *(count + 1 + j + 1));
	i = 0;
	j = 0;
	count = 0;
	while (tab[i])
	{
		if(tab_as_space(tab[i]) == 1)
		{
			tab_i = 0;
			broken_tab = tab_without_space(tab[i], nbr_space(tab[i]));
			while (broken_tab[tab_i])
			{
				new_tab[j] = ft_strcpy(broken_tab[tab_i]);
				tab_i++;
				j++;
			}
			free_double_tab(broken_tab);
		}
		else
			new_tab[j] = ft_strcpy(tab[i]);
	
		i++;
		j++;
	}
	new_tab[j - 1] = NULL;
	
	return (new_tab);
}