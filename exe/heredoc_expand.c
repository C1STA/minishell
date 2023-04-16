/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_expand.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 17:58:58 by wcista            #+#    #+#             */
/*   Updated: 2023/04/16 19:26:49 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"
int has_dollar(char *str)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}
void expand_heredoc(t_heredoc *h, char **env)
{
	int i;
	int j;
	int save;
	char *value;
	char *var;
	printf("c1\n");
	i = 0;
	j = 0;
	if (!h->input)
		return ;
	printf("c2\n");
	while (h->input[i])
	{
		printf("c3\n");
		if (h->input[i] == '$' && h->input[i + 1] && h->input[i + 1] != ' ' && h->input[i + 1] != '\t')
		{
			printf("c4\n");
			i++;
			save = i;
			while (h->input[i] != '\0' && h->input[i] != ' ' && h->input[i] != '\t' && h->input[i] != '$')
			{
				printf("c5\n");
				j++;
				i++;
			}
			var = malloc(sizeof(char) * (j + 1));
			printf("c6\n");
			i = save;
			j = 0;
			while (h->input[i] != '\0' && h->input[i] != ' ' && h->input[i] != '\t' && h->input[i] != '$')
			{
				printf("c7\n");
				var[j] = h->input[i];
				i++;
				j++;
			}
			var[j] = '\0';
			printf("c8\n");
			value = find_value(var, env);
			// transform var par value
			
			printf("c9\n");
			while (has_dollar(h->input) == 1)
				h->input = transform_value(h->input, value);
			printf("c10\n");
		}
		i++;
	}
}

char *find_value(char *str, char **env)
{
	int i;
	int first;
	int last;
	int j;
	char *tmp;

	j = 0;
	i = 0;
	printf("c8.1\n");
	while(env[i])
	{
		first = 0;
		j = 0;
		printf("c8.2\n");
		while(env[i][j]  != '=')
			j++;
		last = j - 1;
		tmp = malloc(sizeof(char) * ((last - first) + 1));
		while (first <= last)
		{
			printf("c8.3\n");
			tmp[first] = env[i][first];
			first++;
		}
		printf("c8.4\n");
		tmp[first] = '\0';
		if (ft_stcmp(str, tmp) == 1)
			return (return_value_heredoc(env[i]));
		printf("c8.5\n");
		free(tmp);
		i++;
	}
	free(str);
	return (NULL);
}

char *return_value_heredoc(char* str)
{
	int i;
	
	i = 0;
	if (!str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (ft_strcpy(str+i));
		}
		i++;
	}
	return (NULL);
}

char *transform_value(char *str, char *value)
{
	char *before_dollar;
	char *after_dollar;
	char *new_str;
	printf("c9.1\n");
	printf("%s\n", str);
	printf("%c\n", str[0]);
	before_dollar = return_before_heredoc(str);
	if (before_dollar)
		printf("b is =>%s\n", before_dollar);
	printf("c9.2\n");
	new_str = ft_strjoin(before_dollar, value);
	if (new_str)
		printf("new str is is =>%s\n", new_str);
	printf("c9.3\n");
	after_dollar = return_after_heredoc(str);
	if (after_dollar)
		printf("after is =>%s\n", after_dollar);
	printf("c9.4\n");
	new_str = ft_strjoin(new_str, after_dollar);
	if (new_str)
		printf("final is =>%s\n", new_str);
	printf("c9.5\n");
	free(str);
	return (new_str);
}
char *return_before_heredoc(char *str)
{
	int i;
	int length;
	char *new_str;

	printf("c9.1.1\n");
	length = 0;
	i = 0;
	printf("%c\n", str[0]);
	while(str[i])
	{
		printf("c9.1.2\n");
		if (str[i] == '$')
			break;
		i++;
		length++;
	}
	printf("c9.1.3\n");
	printf("length is %i\n", length);
	new_str = malloc(sizeof(char) * (length + 1));
	i = 0;
	printf("c9.1.4\n");
	printf("%c\n", str[0]);
	while(str[i])
	{
		printf("c9.1.5\n");
		if (str[i] == '$')
			break;
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	printf("c9.1.6\n");
	return (new_str);
	
}
char *return_after_heredoc(char *str)
{
	int i;
	int j;
	int save;
	char *new_str;
	printf("c9.3.1\n");
	i =  0;
	j = 0;
	while (str[i])
	{
		printf("c9.3.2\n");
		if (str[i] == '$')
		{
			printf("c9.3.2\n");
			i++;
			while (str[i] && str[i] != ' ' && str[i] != '\t')
				i++;
			break;
		}
		i++;
	}
	save = i;
	printf("c9.3.4\n");
	while (str[i])
	{
		printf("c9.3.5\n");
		j++;
		i++;
	}
	new_str = malloc(sizeof(char) * (j + 1));
	printf("c9.3.6\n");
	i = save;
	j = 0;
	while (str[i])
	{
		printf("c9.3.7\n");
		new_str[j] = str[i];
		i++;
		j++;
	}
	printf("c9.3.8\n");
	new_str[j] = '\0';
	return (new_str);
}
