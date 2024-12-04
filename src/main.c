/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wacista <wacista@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:57:56 by imrane            #+#    #+#             */
/*   Updated: 2024/12/04 19:48:09 by wacista          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exe.h"

int		g_exit_status;

void	is_args(int argc)
{
	if (argc > 1)
	{
		ft_putstr_fd("Invalid number of arguments\n", 2);
		exit(1);
	}
}

void	init_main_values(t_main *m, char *env[])
{
	m->final = NULL;
	m->src = NULL;
	m->info = NULL;
	m->root = NULL;
	m->ast = NULL;
	m->final_env = NULL;
	m->mini_env = copy_env(env);
}

void	ft_checker_bis(t_main *m)
{
	supp_quotes(m->root);
	m->ast = create_ast_command_redir(m->root);
	m->final = create_final_ast(m->ast);
	ft_free_before_final_ast(&m->ast);
	final_expand(m->final);
	m->final_env = transform_env_in_double_tab(m->mini_env);
	free_env(&m->mini_env);
	ft_free(NULL, &m->root, &m->src, &m->info);
	executor(m->final, m->final_env, m);
	m->mini_env = copy_env(m->final_env);
	free_final_env(&m->final_env);
	ft_free_final_ast(&m->final);
}

void	ft_checker(t_main *m)
{
	m->root = parse_simple_command(m->input, &m->src, &m->info);
	expand_env(m->mini_env, m->root);
	is_unset(&m->mini_env, m->root);
	if (error_pars(m->root) == 1 && is_env_var(m->mini_env, m->root) == 1)
		ft_checker_bis(m);
	else
		ft_free(NULL, &m->root, &m->src, &m->info);
}

int	main(int argc, char *argv[], char *env[])
{
	t_main	*m;

	is_args(argc);
	ft_signal(1);
	(void)argv;
	m = (t_main *)malloc(sizeof(t_main));
	if (!m)
		return (1);
	init_main_values(m, env);
	while (1)
	{
		m->prompt_name = get_prompt_name(m->mini_env);
		m->input = readline(m->prompt_name);
		free(m->prompt_name);
		if (!m->input)
			ft_exit_d(&m->mini_env, &m);
		add_history(m->input);
		if (single_enter(m->input) == 0 && does_quotes_closed(m->input) == 1
			&& check_space_append_heredoc(m->input) == 1)
			ft_checker(m);
		else
			(free(m->input));
	}
}
