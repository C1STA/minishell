/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_option2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:42:54 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/15 20:09:07 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	pars_env_name_nb_equ(char *str, char *env_input)
{
	if (is_nbr(str[0]) == 1)
	{
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
	return (0);
}

int	pars_env_name_quote(char *str, char *env)
{
	if (str[0] == '"')
	{
		if (str[1])
		{
			if (str[1] == '"')
			{
				if (str[2] == '\0')
				{
					printf("export : '%s' is not a valid identifier\n", env);
					return (1);
				}
			}
		}
	}
	return (0);
}

int	pars_env_name_f_if(char *str, char *env_input, int i)
{
	if (str[i] == ' ' || str[i] == '\t' || str[i] == '@' \
			|| str[i] == '+' || str[i] == '\\' \
			|| str[i] == '(' || str[i] == ')')
	{
		ft_printf("export : '%s' is not a valid identifier\n", env_input);
		return (1);
	}
	return (0);
}

int	pars_env_name_s_if(char *str, char *env_input, int i)
{
	if (str[i] == '*' || str[i] == '{' || str[i] == '}' || str[i] == '-' )
	{
		ft_printf("export : '%s' is not a valid identifier\n", env_input);
		return (1);
	}
	return (0);
}

int	pars_env_name_t_if(char *str, char *env_input, int i)
{
	if (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z') \
			&& !(str[i] >= '0' && str[i] <= '9') \
			&& !(str[i] == '\"') && !(str[i] == '\''))
	{
		ft_printf("export : '%s' is not a valid identifier\n", env_input);
		return (1);
	}
	return (0);
}
