/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:56:53 by wcista            #+#    #+#             */
/*   Updated: 2023/04/04 05:25:41 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXE_H
# define MINISHELL_EXE_H

# include "minishell.h"

typedef struct s_indice
{
	int	i;
	int	i_infile;
	int	i_outfile;
}	t_indice;

typedef struct s_pipex
{
	pid_t	*child;
	int		**fd;
	int		len;
}	t_pipex;

typedef struct s_heredoc
{
	char	*file_name;
	char	*input;
	int		reader;
	int		fd;
}	t_heredoc;

//struct.c
t_final	*init_all(char *txt);
t_final	*addat(t_final *L, int data, int pos);
void	free_all(t_final *cmds);
void	print_struct(t_final *cmds);
int		lenlist(t_final *L);

//pipex.c
void	pipex(t_final *cmds, t_env *env);
void	close_unused_pipes(t_pipex *p, int i);

//pipex_init.c
bool	init_pipes(t_pipex *p);
bool	init_forks(t_final *cmds, t_pipex *p, t_env *env);

//pipex_errors.c
void	free_pipex(t_pipex *p);
bool	pipe_error(t_pipex *p, int i);
bool	fork_error(t_pipex *p);

//heredoc.c
bool	ft_heredoc(t_final *cmds);
void	remove_heredoc(t_final *cmds);

//childs.c
void	child_processs(t_final *cmds, t_pipex *p, int i, t_env *env);

//redir.c
void	redir(t_redir *redir, t_indice *indice);

#endif