/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoupe_ast_no_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:31:15 by imrane            #+#    #+#             */
/*   Updated: 2023/04/10 13:50:09 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_com **create_ast_command_redir(t_node *root)
{
	t_com **ast;
	t_ast  *save_ast;
	t_node *ptr;
	
	int	nbr_pipe;
	int i;
	//printf("c2.1\n");
	save_ast = NULL;
	if (!root)
		return (NULL);
	//printf("c2.2\n");
	ptr = root -> first_child;
	//printf("c2.3\n");
	i = 0;
	nbr_pipe = how_much_pipe(root);
	//printf("nbr of pipe is :%i\n", nbr_pipe);
	//printf("c2.4\n");
	if (nbr_pipe > 0)
	{
		//printf("c2.5\n");
		ast = malloc(sizeof(t_com *) * ((nbr_pipe + 1) + 1));
		ast[(nbr_pipe + 1)] = NULL;
		//printf("c2.6\n");
	}
	else
	{
		//printf("c2.7\n");
		ast = malloc(sizeof(t_com *) + 1);
		ast[1] = NULL;
		nbr_pipe = 0;
		//printf("c2.8\n");
	}


	while (nbr_pipe >= 0)
	{
		//printf("c2.9\n");
		if (save_ast)
		{
			//printf("c2.10\n");
			save_ast = isolate_command_redir(save_ast -> save_ptr);
			//printf("c2.11\n");
		}
		else
		{
			//printf("c2.12\n");
			save_ast = isolate_command_redir(ptr);
			//printf("c2.13\n");
		}
		
		if (save_ast)
		{
			if (save_ast -> command)
			{
				//printf("c2.14\n");
				ast[i] = save_ast -> command;
				//printf("c2.15\n");
			}
			else
			{
				//printf("c2.16\n");
				ast[i] = malloc(sizeof(t_com));
				ast[i] -> txt = NULL;
				//printf("c2.17\n");
			}
			if (ast[i])
			{
				//printf("c2.18\n");
				ast[i] -> redir = save_ast -> redir;
				//printf("c2.19\n");
			}
			free(save_ast);
			i++;
		}
		nbr_pipe--;
	}
	return (ast);
}


t_ast *isolate_command_redir(t_node *ptr)
{
	
	t_ast  *save_ast;
	t_redir *redir;
	t_com	*com;

	if (!ptr)
		return (NULL);
	com = NULL;
	redir = NULL;
	//printf("c2.10.1\n");
	if (ptr)
	{
		//printf("c2.10.2\n");
		if (ptr != NULL)
			//printf("c2.10.2bis\n");
		// quand jenvoie du vide ca bug
		if (ptr -> txt[0] == '\0')
			printf("c2.10.2bis bis\n"); // commentaire wcista
		while (ptr && ft_stcmp(ptr -> txt, "|") != 1)
		{
			//printf("c2.10.3\n");
			// decoupe la command et arguments
			while (ptr && ft_stcmp(ptr -> txt, "|") != 1 && ft_stcmp(ptr -> txt, "<") != 1 && ft_stcmp(ptr -> txt, ">") != 1)
			{
				//printf("c2.10.4\n");
				com = create_com_node(com, ptr);
				ptr = ptr -> next_sibling;
				//printf("c2.10.5\n");
			}
			if (ptr)
			{
				// ok ici en fait javance jusqua pipe
				// alors que jeverai avancer jusquau prochain truc et puis recommencer le processus
				//printf("c2.10.6\n");
				if (ft_stcmp(ptr -> txt, "<") == 1 || ft_stcmp(ptr -> txt, ">") == 1 )
				{
					//printf("c2.10.7\n");
						if ((ptr -> next_sibling  && ft_stcmp(ptr -> next_sibling -> txt, "<") == 1) || (ptr -> next_sibling  && (ft_stcmp(ptr -> next_sibling -> txt, ">") == 1 )))
						{
							//printf("c2.10.8\n");
							if (ptr && ft_stcmp(ptr -> txt, "|") != 1)
							{
								//printf("c2.10.9\n");
								redir = create_redir_node(redir, ptr);
								//printf("c2.10.10\n");
							}
							if (ptr && ft_stcmp(ptr -> txt, "|") != 1)
							{
								//printf("c2.10.11\n");
								ptr = ptr -> next_sibling;
								//printf("c2.10.12\n");
							}
							if (ptr && ft_stcmp(ptr -> txt, "|") != 1)
							{
								//printf("c2.10.13\n");
								ptr = ptr -> next_sibling;
								//printf("c2.10.14\n");
							}
							if (ptr && ft_stcmp(ptr -> txt, "|") != 1)
							{
								//printf("c2.10.15\n");
								redir = create_redir_node(redir, ptr);
								//printf("c2.10.16\n");
							}
						}
						else if (ptr && ft_stcmp(ptr -> txt, "|") != 1)
						{
							//printf("c2.10.17\n");
							if (ptr && ft_stcmp(ptr -> txt, "|") != 1)
							{
								//printf("c2.10.18\n");
								redir = create_redir_node(redir, ptr);
								//printf("c2.10.19\n");
							}
							if (ptr )
							{
								//printf("c2.10.20\n");
								ptr = ptr -> next_sibling;
								//printf("c2.10.21\n");
							}
	
							if (ptr && ft_stcmp(ptr -> txt, "|") != 1) 
							{
								//printf("c2.10.22\n");
								redir = create_redir_node(redir, ptr);
								//printf("c2.10.23\n");
							}
						}
						if (ptr && ft_stcmp(ptr -> txt, "|") != 1)
						{
							//printf("c2.10.24\n");
							ptr = ptr -> next_sibling;
							//printf("c2.10.25\n");
						}
				}
			}
		}
	// avance prochaine command
		if (ptr)
		{
			//printf("c2.10.26\n");
			ptr = ptr -> next_sibling;
			//printf("c2.10.27\n");
		}
		// sauvegarde debut prochainne command + redir + command
		save_ast = malloc(sizeof(save_ast));
		//printf("c2.10.28\n");
		if (com)
		{
			//printf("c2.10.29\n");
			save_ast -> command = com;
			//printf("c2.10.30\n");
		}
		else
		{
			//printf("c2.10.31\n");
			save_ast -> command = NULL;
			//printf("c2.10.32\n");
		}
			
		if (redir)
		{
			//printf("c2.10.33\n");
			save_ast -> redir = redir;
			//printf("c2.10.34\n");
		}
		else
		{
			//printf("c2.10.35\n");
			save_ast -> redir = NULL;
			//printf("c2.10.36\n");
		}
			
		if (ptr)
		{
			//printf("c2.10.37\n");
			save_ast -> save_ptr = ptr;
			//printf("c2.10.38\n");
		}
	}
	return (save_ast);
}

void print_final_ast(t_com **ast)
{
	int i;
	i = 0;
	while(ast[i])
	{
		
		//ft_printf("------------------------\n");
		//printf("command %i is :\n", i);
		print_command(ast[i]);
		print_redir(ast[i] -> redir);
		//ft_printf("------------------------\n");
		i++;
	}
}

void print_command(t_com *com)
{
	t_com *ptr;
	if (!com)
	{
		//printf("there is nos command\n");
		return ;
	}
	ptr = com;
	while (ptr)
	{
		//ft_printf("command is \n");
		//ft_printf("%s\n",ptr -> txt);
		ptr = ptr -> next_sibling;
	}
}
void print_redir(t_redir *redir)
{
	t_redir *ptr;
	if (!redir)
	{
		//ft_printf("there is no redir for this command\n");
		return ;
	}
	ptr = redir;
	while (ptr)
	{
		//ft_printf("redir is \n");
		//ft_printf("%s\n",ptr -> txt);
		ptr = ptr -> next_sibling;
	}
}

