/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manip_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imrane <imrane@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/19 18:47:11 by imrane            #+#    #+#             */
/*   Updated: 2023/03/10 20:13:20 by imrane           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char    *ft_strcpy(char *str)
{
	int i;
	int length;
	char *ptr;
	
	if (!str)
		return (NULL);
	i = 0;
	length = ft_strlen(str);
	ptr = malloc((sizeof(char) *length) + 1);
	if (!ptr)
		return (NULL);
	while (str[i])
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
char    *ft_strcpy_env(char *str)
{
	int i;
	int length;
	char *ptr;
	
	if (!str)
		return (NULL);
	i = 0;
	length = ft_strlen(str);
	ptr = malloc((sizeof(char) *length) + 1);
	if (!ptr)
		return (NULL);
	while (str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

t_env	*new_node_env(void)
{
	t_env *node;
	
	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node -> next = NULL;
	node -> txt = NULL;
	node -> var_name = NULL;
	node -> var_value = NULL;
	return (node);
}
t_env   *add_node_env(t_env *head)
{
	t_env *ptr;
	if (!head)
		return (NULL);
	ptr = head;
	if (head -> next == NULL)
	{
		head -> next = new_node_env();
		return (head);
	}
	else
	{
		while (ptr -> next != NULL)
			ptr = ptr -> next;
		ptr -> next = new_node_env();
	}
	return (head);
}

void    create_var_value(t_env *node)
{
	int i;
	int equal;

	if (!node)
		return ;
	if (node -> txt == NULL)
		return ;
	equal = 0;
	while(node -> txt[equal] != '=')
		equal++;
	i = equal;
	while (node -> txt[i] != '\0')
		i++;
	node -> var_value = malloc((sizeof(char) *(i - equal)) + 1);
	if (node -> var_value == NULL)
		return ;
	i = 0;
	equal++;
	while(node -> txt[equal] != '\0')
	{
		node -> var_value[i] = node -> txt[equal];
		i++;
		equal++;
	}
	node ->var_value[i] = '\0';
}

void    create_var_name(t_env *node)
{
	int i;
	
	if (!node)
		return ;
	if (node -> txt == NULL)
		return ;
	i = 0;
	while(node -> txt[i] != '=')
		i++;
	node -> var_name = malloc((sizeof(char))*i + 1);
	if (node -> var_name == NULL)
		return ;
	i = 0;
	while(node -> txt[i] != '=')
	{
		node -> var_name[i] = node -> txt[i];
		i++;
	}
	node ->var_name[i] = '\0';
}

t_env   *copy_env(char *original[])
{
    int i;
	t_env *mini_env;
	t_env	*ptr;

	i = 0;
	if (!original || original[0] == NULL)
		return (NULL);
	mini_env = malloc(sizeof(t_env));
	if (mini_env == NULL)
		return (NULL);
	mini_env -> next = NULL;
	while (original[i])
		i++;
	while(i > 1)
	{
		mini_env = add_node_env(mini_env);
		i--;
	}
	i--;
	ptr = mini_env;
	while (original[i] && ptr != NULL)
	{
		ptr -> txt = ft_strcpy(original[i]);
		ptr = ptr -> next;
		i++;
	}
	ptr = mini_env;
	while(ptr != NULL)
	{
		create_var_name(ptr);
		create_var_value(ptr);
		ptr = ptr -> next;
	}
	return (mini_env);
}

void    print_env(t_env *head)
{
	t_env *ptr;
	if (!head)
		return ;
	ptr = head;
	while (ptr != NULL)
	{
		ft_printf("%s\n", ptr -> txt);
		//printf("var name :%s\n", ptr -> var_name);
		//printf("var value :%s\n", ptr -> var_value);
		ptr = ptr -> next;
	}
}
int		ft_stcmp(char *str1, char *str2)
{
	int i;

	i = 0;
	if (!str1 || !str2)
		return (0);
	while (str1[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (0);
		i++;
	}
	return (1);
}

int     is_nbr(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}
void     is_env_var(t_env *mini_env, t_node *root)
{
	t_node *ptr;
	if (!root)
		return ;
	ptr = root -> first_child;
	if (ptr)
	{
		if (ft_stcmp(ptr -> txt, "export") && (ptr -> next_sibling != NULL))
			insert_input_env(mini_env, root);
		ptr = ptr -> next_sibling;
	}
}
char	*extract_name(char *str)
{
	int i;
	char *ptr;
	
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != '=')
		i++;
	ptr = malloc((sizeof(char) *i) + 1);
	if (!ptr)
		return (NULL);
	i = 0;
	while (str[i] != '=')
	{
		ptr[i] = str[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
char	*extract_value(char *str)
{
	int i;
	int equal;
	char *ptr;
	
	i = 0;
	equal = 0;
	if (!str)
		return (NULL);
	while (str[i] != '=')
		i++;
	equal = i;
	while(str[i] != '\0' && str[i] != ' ' && str[i] != '\t')
		i++;
	ptr = malloc( (sizeof(char)) *(i - equal) + 1);
	if (!ptr)
		return (NULL);
	equal++;
	i = 0;
	while (str[equal] != '\0' && str[equal] != ' ' && str[equal] != '\t')
	{
		ptr[i] = str[equal];
		i++;
		equal++;
	}
	ptr[i] = '\0';
	return (ptr);
}

t_env	*last_env_node(t_env *head)
{
	t_env *ptr;
	
	ptr = head;
	if (!ptr)
		return (NULL);
	while (ptr -> next != NULL)
		ptr = ptr -> next;
	return (ptr);
}
void    insert_input_env(t_env *head, t_node *root)
{
	char *var_env_name;
	char *var_env_value;
	char *env_input;
	t_env	*last_node;

	if (!head || !root)
		return ;
	if ((root -> first_child == NULL))
		return ;
	if ((root -> first_child -> next_sibling == NULL))
		return ;
	env_input = ft_strcpy_env(root -> first_child -> next_sibling -> txt);
	var_env_name = extract_name(root -> first_child -> next_sibling -> txt);
	var_env_value = extract_value(root -> first_child -> next_sibling -> txt);
	add_node_env(head);
	last_node = last_env_node(head);
	last_node -> var_name = var_env_name;
	last_node -> var_value = var_env_value;
	last_node -> txt = env_input;
}
t_node		*do_i_have_to_expand(t_node *node)
{
	t_node *ptr;

	if (!node)
		return (NULL);
	ptr = node;
	if (ptr != NULL)
	{
		if (ptr -> txt[0] == '$')
			return (ptr);
		ptr = ptr -> next_sibling;
	}
	return (NULL);
}
char	*return_matching_value(t_env *head, char *str)
{
	t_env *ptr;

	ptr = head;
	if (!ptr || !str)
		return (NULL);
	while (ptr != NULL)
	{
		if (ft_stcmp(str, ptr -> txt) == 1)
			return (ptr -> var_value);
		ptr = ptr -> next;
	}
	return (NULL);
}

void	cut_dollar_sign(char *str)
{
	int i;
	int length;

	i = 0;
	length = ft_strlen(str);
	while (str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	length = length -1;
	str[length] = '\0';
}

void    expand_env(t_env *head, t_node *root)
{
	t_node *ptr;
	t_node *expand;
	char	*str;

	if (!head || !root)
		return ;
	ptr = root -> first_child;
	if (is_here_doc(root) == 1)
		return ;
	while (ptr)
	{
		expand = do_i_have_to_expand(ptr);
		if (expand)
		{
			cut_dollar_sign(expand -> txt);
			str = ft_strcpy(return_matching_value(head, expand -> txt));
			free(expand -> txt);
			expand -> txt = str;
		}
		ptr = ptr -> next_sibling;
	}
}