/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:57:56 by imrane            #+#    #+#             */
/*   Updated: 2023/03/30 17:14:13 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	struct sigaction action_exit;
	sigset_t	sigmask;

	sigemptyset(&sigmask);
	action_exit.sa_flags = SA_SIGINFO;
	action_exit.sa_mask = sigmask;
	action_exit.sa_sigaction = ft_sigint;
	sigaction(SIGINT, &action_exit, NULL);
	// programme hors signaux
	mini_env = copy_env(env);
    src = NULL;
	info = NULL;
	root = NULL;
	ast = NULL;
		
	while (1)
    {
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
        		printf("----------------------\n");
				print_env(mini_env);
				printf("----------------------\n");
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
				define_heredoc(final);
				remove_heredoc(final);
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