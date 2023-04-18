/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_with_option2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/15 19:42:54 by imoumini          #+#    #+#             */
/*   Updated: 2023/04/18 02:55:07 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

extern int	g_exit_status;

int	pars_env_name_nb_equ(char *str, char *env_input)
{
	if (is_nbr(str[0]) == 1)
		return (print_error_export(env_input), 1);
	if (str[0] == '=')
		if (str[1] == '\0')
			return (print_error_export(env_input), 1);
	return (0);
}

int	pars_env_name_quote(char *str, char *env)
{
	if (str[0] == '"')
		if (str[1])
			if (str[1] == '"')
				if (str[2] == '\0')
					return (print_error_export(env), 1);
	return (0);
}

int	pars_env_name_f_if(char *str, char *env_input, int i)
{
	if (str[i] == ' ' || str[i] == '\t' || str[i] == '@' \
			|| str[i] == '+' || str[i] == '\\' \
			|| str[i] == '(' || str[i] == ')')
		return (print_error_export(env_input), 1);
	return (0);
}

int	pars_env_name_s_if(char *str, char *env_input, int i)
{
	if (str[i] == '*' || str[i] == '{' || str[i] == '}' || str[i] == '-' )
		return (print_error_export(env_input), 1);
	return (0);
}

int	pars_env_name_t_if(char *str, char *env_input, int i)
{
	if (!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z') \
			&& !(str[i] >= '0' && str[i] <= '9') \
			&& !(str[i] == '\"') && !(str[i] == '\''))
		return (print_error_export(env_input), 1);
	return (0);
}
