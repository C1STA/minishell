/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:56:53 by wcista            #+#    #+#             */
/*   Updated: 2023/04/12 06:40:17 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXE_H
# define MINISHELL_EXE_H

# include "minishell.h"

typedef struct s_pipex
{
	pid_t	*child;
	int		**fd;
	int		nb_cmds;
	int		i;
	int		exit_status;
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
void	pipex(t_final *cmds, t_env *mini_env);
void	close_unused_pipes(t_pipex *p);

//pipex_init.c
bool	init_pipes(t_pipex *p);
bool	init_forks(t_final *cmds, t_pipex *p, t_env *mini_env);

//pipex_errors.c
void	free_pipex(t_pipex *p);
bool	pipe_error(t_pipex *p);
bool	fork_error(t_pipex *p);

//heredoc.c
bool	ft_heredoc(t_final *cmds, t_env *mini_env);
void	remove_heredoc(t_final *cmds);
char	*heredoc_file_name(int i, int j);

//childs.c
void	child_processs(t_final *cmds, t_pipex *p, t_env *mini_env);

//redir.c
bool	init_redir(t_redir *redir, t_pipex *p);

//redir_utils.c
bool	redir_infile(t_redir *redir, t_pipex *p);
bool	redir_heredoc(t_redir *redir, t_pipex *p, int j);
bool	redir_outfile(t_redir *redir, t_pipex *p);
bool	redir_append(t_redir *redir, t_pipex *p);

//strjoin_free
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_strcmp(const char *s1, const char *s2);

//free
void	free_exe(t_final **cmds, t_env **mini_env);
void	exit_child(t_final *cmds, t_pipex *p, t_env *mini_env);

//print
void	print_perror(char *s);
void	print_exit(char *s, bool n, t_pipex *p);
void	print_exec(char *s, t_pipex *p);

//builtin
bool	builtin_exe(t_final *cmds, t_pipex *p);

#endif