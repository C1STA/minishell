/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <imoumini@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/24 22:06:18 by imrane            #+#    #+#             */
/*   Updated: 2023/04/23 17:17:33 by imoumini         ###   ########.fr       */
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
			if (ptr_node -> next != NULL)
			{
				while (ptr_node -> next != NULL)
				{
					save = ptr_node -> next;
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

void free_final_env(char ***tab_env)
{
	int i;
	char **tab;
	i = 0;

	if (!tab_env)
		return ;
	tab = *tab_env;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab_env = NULL;
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
	
	if (!ast_before)
		return ;
	ast = *ast_before;
	if (!ast)
		return ;
	while (ast[i])
	{
		ptr = ast[i];
		while (ptr)
		{
			save_ptr = ptr -> next;
			if (ptr -> txt)
			{
				free(ptr -> txt);
				ptr -> txt = NULL;
			}
			free(ptr);
			ptr = save_ptr;
		}
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
	if (!ast)
		return;
	i = 0;
	while (ast)
	{
		save_ast = ast -> next;
		while (ast -> cmds[i])
		{
			free(ast -> cmds[i]);
			ast -> cmds[i] = NULL;
			i++;
		}
		free(ast -> cmds);
		while (ast -> redir)
		{
			save_redir = ast -> redir -> next;
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
			ptr = NULL;
		}
		else
			free(ptr);
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

void free_expand_job_mutiple(char *str_nbr, char *dollar, char *txt)
{
	free(dollar);
	free(txt);
	free (str_nbr);
}
