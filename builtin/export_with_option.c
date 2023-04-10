/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_option.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 17:16:25 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/10 13:27:22 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int     is_env_var(t_env *mini_env, t_node *root)
{
	t_node *ptr;
	int nbr;
	if (!root)
		return (1);
	//printf("c0.1\n");
	nbr =  how_much_pipe(root);
	//printf("nbr of pipe is %i\n", nbr);
	ptr = root -> first_child;
	//printf("c0.2\n");
	if (ptr)
	{
		//printf("c0.3\n");
		if (ft_stcmp(ptr -> txt, "export") && (ptr -> next_sibling != NULL))
		{
			//printf("c0.4\n");
			if (insert_input_env(&mini_env, ptr, nbr) == 0)
			{
				//printf("c0.5\n");
				return (0);
			}
		}
		ptr = ptr -> next_sibling;
		//printf("c0.6\n");
	}
	// faut que le retour de ske g pas le droit je le recois la comme ca je vais pas dans
	// la suite
	return (1);
}

int count_nbr_equal(char *str, char *env_input)
{
	int i;
	int count;
	
	//printf("c0.4.4.16\n");
	//printf("%s\n", env_input);
	count = 0;
	i = 0;
	//printf("c0.4.4.17\n");
	while (str[i])
	{
		//printf("c0.4.4.18\n");
		printf("str[i] =>%c\n", str[i]);
		if (str[i] == '=')
		{
			//printf("c0.4.4.19\n");
			count++;
		}
		//printf("c0.4.4.20\n");
		i++;
	}
	if (count == 0)
	{
		//printf("c0.4.4.21\n");
		ft_printf("export : '%s' is not a valid identifier\n", env_input);
		return (1);
	}
	//printf("c0.4.4.22\n");
	return (0);
}
int pars_env_name(char *str, char *env_input)
{
	int i;
	i = 0;
	//printf("c0.4.4.1\n");
	if (!str)
		return (1);
	if (!env_input)
		return (1);
	//printf("c0.4.4.2\n");
	if (is_nbr(str[0]) == 1)
	{
		//printf("c0.4.4.3\n");
		ft_printf("export : '%s' is not a valid identifier\n", env_input);
		return (1);
	}
	
	if (str[0] == '=')
	{
		if (str[1] == '\0')
		{
			ft_printf("export : '%s' is not a valid identifier\n", env_input);
			return (1);
		}
	}
	
	if (str[0] == '"')
	{
		if (str[1])
		{
			if (str[1] == '"')
			{
				if (str[2] == '\0')
				{
					ft_printf("export : '%s' is not a valid identifier\n", env_input);
					return (1);
				}
			}
		}
	}
	while (str[i])
	{
		//printf("c0.4.4.4\n");
		// choisir les bons messages d'erreur
		if (str[i] == ' ' || str[i] == '\t' || str[i] == '@' || str[i] == '+' || str[i] == '\\' || str[i] == '(' || str[i] == ')')
		{
			//printf("c0.4.4.5\n");
			ft_printf("export : '%s' is not a valid identifier\n", env_input);
			return (1);
		}
		if (str[i] == '*' || str[i] == '{' || str[i] == '}' || str[i] == '-' )
		{
			//printf("c0.4.4.6\n");
			ft_printf("export : '%s' is not a valid identifier\n", env_input);
			return (1);
		}	
		if (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z') && !(str[i] >= '0' && str[i] <= '9') && !(str[i] == '\"') && !(str[i] == '\''))
		{
			//printf("c0.4.4.7\n");
			ft_printf("export : '%s' is not a valid identifier\n", env_input);
			return (1);
		}	
		i++;
		//printf("c0.4.4.8\n");
	}
	//printf("c0.4.4.9\n");
	return (0);
}

int pars_env_value(char *str, char *env_input)
{
	int i;
	i = 0;
	
	//printf("c0.4.4.10\n");
	if (!str)
		return (0);
	if (!env_input)
		return (1);
	//printf("c0.4.4.11\n");
	while (str[i])
	{
		//printf("c0.4.4.12\n");
		if ( str[i] == '\\')
		{
			//printf("c0.4.4.13\n");
			ft_printf("export : '%s' is not a valid identifier\n", env_input);
			return (1);
		}
		//printf("c0.4.4.14\n");
		i++;
	}
	//printf("c0.4.4.15\n");
	return (0);
}