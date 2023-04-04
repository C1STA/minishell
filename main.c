/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:57:56 by imrane            #+#    #+#             */
/*   Updated: 2023/04/04 05:22:07 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

bool	ft_builtin_check(t_final *cmds)
{
	if ((!ft_strcmp(cmds->cmds[0], "test")) && cmds->cmds[1] == NULL)
		return (false);
	return (true);
}

int main(int argc, char *argv[], char *env[])
{
    t_env	*mini_env;
	char *input;
    t_source *src;
    t_info_tok *info;
    t_node *root;
	t_com **ast;
	t_final *final;
	(void)argc;
    (void)argv;

	// signal exit
//	ft_signal(1);
	//g_exit_status = 0;

	// programme hors signaux
	mini_env = copy_env(env);
    src = NULL;
	info = NULL;
	root = NULL;
	ast = NULL;

	while (1)
    {
		printf("ggggg=%d\n", g_exit_status);
		ft_signal(1);
        input = readline("minishell> ");
		if (single_enter(input) == 0)
		{
			root = parse_simple_command(input, &src, &info);
			print_ast(root);
			ft_exit(&mini_env, &root, &src, &info);
			if(error_pars(root) == 1)
			{
				is_env_var(mini_env, root);
				//afficher env apres que j'ai ajouté var env
        		printf("1----------------------\n");
				print_env(mini_env);
				printf("2----------------------\n");
				// afficher ast avant expand
				print_ast(root);
				printf("----------------------\n");
				if(is_there_quotes(root) == 0)
				{
					printf("c1\n");
					expand_env(mini_env,root);
					printf("c2\n");
					ast = create_ast_command_redir(root);
					printf("c3\n");
				}
				/*
				// jpense finalement jvai inclure single guillemets et double guillemets dans le meme if
				// genre je vais au sein de chaque fonction gerer le cas du single et double en meme temps
				// je parcours, des que je vois une guillemet
				// je vois de quel type de guilleemts
				// je fais ske g a faire jusqua la prochainne guillemets
				// puis ca continue
				if(is_there_quotes(root) == 1)
				{
					if(is_there_both(root) == 0)
					{
						if(is_there_single_quotes(root) == 1)
						{
							
						}
						if(is_there_double_quotes(root) == 1)
						{
							
						}
					}
					else
					{
						// isoler les single quote faire ski a a faire
						// isoler les double quotes faire ski ya a faire
					}
				
				}
				*/
				printf("-----------------------\n");
				printf("ast after expand is : \n");
				print_ast(root);
				printf("c4\n");
				printf("----------------------\n");
				printf("final ast is :\n");
				final = create_final_ast(ast);
				ft_free_before_final_ast(&ast);
				printf("c5\n");
				printf_final_ast(final);
				printf("c6\n");
				executor(final, mini_env);
				remove_heredoc(final);
/* 				if (ft_builtin_check(final) == false)
					printf("OKkk\n");
				else
					printf("kkKO\n"); */
				
				//printf ("redir ==___%s____\n", final->redir->txt);
				//final->redir = final->redir->next_sibling;
				//printf("2ND_redir==========___%s___=\n", final->redir->txt);
			}
			ft_free(NULL, &root, &src,&info);
			ft_free_final_ast(&final);
		}
			else (free(input));
    }
}

// regler les invalid write, conditionnal jump et invalid free

   // faire ctrl c fait rien
// faire ctr D -> quitte le shell
// faire ctrl \ -> ne fait rien
// demande à matthieu les guillemets
// faire historique
// rendre la structure avec tout bien fait pour que l'execution soit simple
// export sans option

// faire norminette

// si des guillemets
	// simple guillemets
	// double guillemets

// valgrind