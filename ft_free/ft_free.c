/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 22:06:18 by imrane            #+#    #+#             */
/*   Updated: 2023/04/04 20:17:46 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
void free_ast(t_node **root)
{
	t_node *ptr_root;
	t_node *ptr_node;
	t_node *save;
	if (!root)
		return ;
	ptr_root = *root;
	if (ptr_root)
	{
		ptr_node = ptr_root -> first_child;
		if (ptr_node)
		{
			if (ptr_node -> next_sibling != NULL)
			{
				while (ptr_node -> next_sibling != NULL)
				{
					save = ptr_node -> next_sibling;
					free(ptr_node -> txt);
					free(ptr_node);
					ptr_node = save;
				}
				free(ptr_node -> txt);
				free(ptr_node);
			}
			else
			{
				free(ptr_node -> txt);
				free(ptr_node);
			}
		}
		free(ptr_root);
		root = NULL;
		
	}
	free(root);
	root = NULL;
}
void free_env(t_env **mini_env)
{
	t_env *ptr_env;
	t_env *save_env;

	if (!mini_env)
		return ;
	ptr_env = *mini_env;
	if (ptr_env)
	{
		while (ptr_env -> next != NULL)
		{
			save_env = ptr_env -> next;
			free(ptr_env -> txt);
			free(ptr_env -> var_name);
			free(ptr_env -> var_value);
			free(ptr_env);
			ptr_env = save_env;
		}
		free(ptr_env -> txt);
		free(ptr_env -> var_name);
		free(ptr_env -> var_value);
		free(ptr_env);
		mini_env = NULL;
	}
}
void ft_free(t_env **mini_env, t_node **root, t_source **src, t_info_tok **info) 
{
	if (root)
		free_ast(root);
	if (mini_env)
		free_env(mini_env);
	if (src)
		free_src(src);
	if (info)
		free_info(info);
}

void ft_free_before_final_ast(t_com ***ast_before)
{
	int i;
	i = 0;
	t_com **ast;
	t_com *ptr;
	t_com *save_ptr;
	printf("c5.1\n");
	if (!ast_before)
		return ;
	ast = *ast_before;
	if (!ast)
		return ;
		// double tableau ou chaue tab est une command
		// les command sont des lisst chainee de ype t_com
		// free pas les redir car ca je le free dans la final ast
	printf("c5.2\n");
	// command 1
	while (ast[i])
	{
		printf("c5.3\n");
		// contenu du premier element de command 1 mais je vais pas aux autes elements
		ptr = ast[i];
		while (ptr)
		{
			save_ptr = ptr -> next_sibling;
			if (ptr -> txt)
			{
				printf("c5.4\n");
				printf("ast i com is =>%s\n", ptr -> txt);
				free(ptr -> txt);
				ptr -> txt = NULL;
			}
			free(ptr);
			ptr = save_ptr;
		}
		//free(ast[i]);
		printf("c5.5\n");
		ast[i] = NULL;
		i++;
	}
	free(ast);
	printf("c5.6\n");
	ast_before = NULL;
}

void ft_free_final_ast(t_final **ast_before)
{
	t_final *ast;
	t_final *save_ast;
	t_redir *save_redir;
	
	int i;
	printf("c9.1\n");
	if (!ast_before)
		return ;
	printf("c9.2\n");
	ast = *ast_before;
	if (!ast)
		return;
	printf("c9.3\n");
	i = 0;
	while (ast)
	{
		printf("c9.4\n");
		save_ast = ast -> next_sibling;
		while (ast -> cmds[i])
		{
			printf("c9.5\n");
			printf("%s\n", ast -> cmds[i]);
			free(ast -> cmds[i]);
			ast -> cmds[i] = NULL;
			i++;
		}
		free(ast -> cmds);
		printf("c9.6\n");
		while (ast -> redir)
		{
			printf("c9.7\n");
			save_redir = ast -> redir -> next_sibling;
			if (ast -> redir -> txt)
				free(ast -> redir -> txt);
			ast -> redir -> txt = NULL;
			if (ast -> redir)
				free(ast -> redir);
			ast -> redir = NULL;
			ast -> redir = save_redir;
		}
		printf("c9.8\n");
		i = 0;
		free(ast);
		ast = save_ast;
		printf("c9.9\n");
	}
	ast_before = NULL;
	printf("c9.10\n");
}

void free_info(t_info_tok **info)
{
	t_info_tok *ptr;
	if (info)
	{
		ptr = *info;
		if (ptr)
		{
			if (ptr -> tok_buf)
			{
				free(ptr -> tok_buf);
				ptr -> tok_buf = NULL;
			}
			free(ptr);
		}
		info = NULL;
	}
}
void free_src(t_source **src)
{
	t_source *ptr;
	if (src)
	{
		ptr = *src;
		if (ptr)
		{
			if (ptr -> buffer)
			{
				free (ptr -> buffer);
				ptr -> buffer = NULL;
			}
			free(ptr);
		}
		src = NULL;
	}
}
void free_tok(t_token **tok)
{
	t_token *ptr;
	
	if (tok)
	{
		ptr = *tok;
		if (ptr)
		{
			if (ptr -> text)
			{
				if (ptr -> text)
				{
					free(ptr-> text);
					ptr -> text = NULL;
				}
				ptr -> text = NULL;
			}
			free(ptr);
		}
		tok = NULL;
	}
}
void free_info_buf(t_info_tok *info)
{
	t_info_tok *ptr;
	
	if (info)
	{
		ptr = info;
		if (ptr)
		{
			if (ptr -> tok_buf)
			{
				free(ptr -> tok_buf);
				ptr -> tok_buf = NULL;
			}
			ptr -> tok_buf = NULL;
		}
	}
}