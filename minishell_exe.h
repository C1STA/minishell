/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exe.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 15:56:53 by wcista            #+#    #+#             */
/*   Updated: 2023/04/20 01:53:42 by wcista           ###   ########.fr       */
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
	int		len;
	int		i;
	int		i_save;
	int		j;
	int		k;
	int		dollar;
	char	*tmp;
	char	*dest;
	char	*file_name;
	char	*input;
	int		reader;
	int		fd;
}	t_heredoc;

typedef struct s_cd
{
	char	*cwd;
	char	*path;
	char	*tmp;
}	t_cd;

typedef struct s_export
{
	int		i;
	int		j;
	int		min_idx;
	int		len;
}	t_export;

//builtin_cd.c
bool	print_perror_cd(char *s, bool n, t_pipex *p, t_cd *cd);

//pipex.c
void	pipex(t_final *cmds, char *env[]);
void	close_unused_pipes(t_pipex *p);

//pipex_init.c
bool	init_pipes(t_pipex *p);
bool	init_forks(t_final *cmds, char *env[], t_pipex *p);

//pipex_errors.c
void	free_pipex(t_pipex *p);
bool	pipe_error(t_pipex *p, int i);
bool	fork_error(t_pipex *p);

//heredoc.c
bool	ft_heredoc(t_final *cmds, char *env[]);
void	remove_heredoc(t_final *cmds);
char	*heredoc_file_name(int i, int j);
char	*heredoc_expand(t_heredoc *h, char *env[]);
char	*heredoc_expanded(t_heredoc *h, char *env[]);
int		env_var_len(char *env);
/*
void	expand_heredoc(t_heredoc *h, char **env);
char	*find_value(char *str, char **env);
char	*return_value_heredoc(char *str);
char	*transform_value(char *str, char *value);
char	*return_before_heredoc(char *str);
char	*return_after_heredoc(char *str);
*/
//childs.c
void	child_processs(t_final *cmds, char *env[], t_pipex *p);

//redir.c
bool	init_redir(t_redir *redir, t_pipex *p);

//redir_utils.c
bool	redir_infile(t_redir *redir, t_pipex *p);
bool	redir_heredoc(t_redir *redir, t_pipex *p, int j);
bool	redir_outfile(t_redir *redir, t_pipex *p);
bool	redir_append(t_redir *redir, t_pipex *p);

//free
void	free_exe(t_final **cmds, char ***env);
void	exit_exe(t_final *cmds, char *env[], t_pipex *p);

//print
void	print_perror(char *s);
void	print_exit(t_final *cmds, t_pipex *p, char *s, bool n);
void	print_exec(char *s, t_pipex *p);

//builtin
bool	isbuiltin(t_final *cmds);
bool	builtin_exe(t_final *cmds, char *env[], t_pipex *p);
bool	builtin_exe_cd(t_final *cmds, char *env[], t_pipex *p);
bool	builtin_exe_export(char *env[], t_pipex *p);

//utils
int		lenlist(t_final *L);
void	ft_swap(char **a, char **b);
void	ft_free_str(char **str);
char	*ft_strjoin_env(char *s1, char *s2);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_strcmp(const char *s1, const char *s2);
size_t	ft_tablen(char **t);
int		ft_strcmp_e(char *s1, char *s2);

#endif