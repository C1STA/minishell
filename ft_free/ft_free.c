/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 22:06:18 by imrane            #+#    #+#             */
/*   Updated: 2023/03/19 19:03:14 by imoumini         ###   ########.fr       */
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
	if (!ast_before)
		return ;
	ast = *ast_before;
	if (!ast)
		return ;
		// double tableau ou chaue tab est une command
		// les command sont des lisst chainee de ype t_com
		// free pas les redir car ca je le free dans la final ast
	while (ast[i])
	{
		if (ast[i] -> txt)
		{
			free(ast[i] -> txt);
			ast[i] -> txt = NULL;
		}
		free(ast[i]);
		ast[i] = NULL;
		i++;
	}
	free(ast);
	ast_before = NULL;
}

void ft_free_final_ast(t_final **ast_before)
{
	t_final *ast;
	t_final *save_ast;
	t_redir *save_redir;
	
	int i;

	if (!ast_before)
		return ;
	ast = *ast_before;
	if (ast)
		return;
		
	while (ast)
	{
		save_ast = ast -> next_sibling;
		while (ast -> cmds[i])
		{
			free(ast -> cmds[i]);
			ast -> cmds[i] = NULL;
			i++;
		}
		while (ast -> redir)
		{
			save_redir = ast -> redir -> next_sibling;
			if (ast -> redir -> txt)
				free(ast -> redir -> txt);
			ast -> redir -> txt = NULL;
			if (ast -> redir)
				free(ast -> redir);
			ast -> redir = NULL;
			ast -> redir = save_redir;
		}
		i = 0;
		free(ast);
		ast = save_ast;
	}
	ast_before = NULL;
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