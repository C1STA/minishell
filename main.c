/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/03 20:57:56 by imrane            #+#    #+#             */
/*   Updated: 2023/04/22 22:22:15 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "minishell_exe.h"

int	g_exit_status;

int main(int argc, char *argv[], char *env[])
{
    t_env	*mini_env;
	char *input;
    t_source *src;
    t_info_tok *info;
    t_node *root;
	t_com **ast;
	t_final *final;
	char **final_env;
	t_env *last_node;
	char *exit_status;
	//char	*prompt_name;
	(void)argc;
    (void)argv;
	
	// signal exit
	struct sigaction action_exit;
	sigset_t	sigmask;

	g_exit_status = 0;
	sigemptyset(&sigmask);
	action_exit.sa_flags = SA_SIGINFO;
	action_exit.sa_mask = sigmask;
	action_exit.sa_sigaction = ft_sigint;
	sigaction(SIGINT, &action_exit, NULL);
	
	// signal control D
	signal(SIGQUIT, SIG_IGN);
	// programme hors signaux
	mini_env = copy_env(env);
	final = NULL;
    src = NULL;
	info = NULL;
	root = NULL;
	ast = NULL;
	final_env = NULL;
	while (1)
	{
		//prompt_name = get_prompt_name(mini_env);
		input = readline("minishell> ");
		//free(prompt_name);
		if (!input)
			ft_exit_d(&mini_env);
		add_history(input);
		if (single_enter(input) == 0 && does_quotes_closed(input) == 1 && check_space_append_heredoc(input) == 1)
		{
			root = parse_simple_command(input, &src, &info);
			if (check_if_exist(mini_env, "?") == 1)
				supp_env(&mini_env, "?");
			add_node_env(mini_env);
			last_node = last_env_node(mini_env);
			exit_status = ft_itoa(g_exit_status);
			fill_last_node(last_node, ft_strcpy("?"), exit_status, ft_strjoin(ft_strcpy("?="), exit_status));
			expand_env(mini_env,root);
			is_unset(&mini_env, root);
			if(error_pars(root) == 1 && is_env_var(mini_env, root) == 1)
			{
				supp_quotes(root);
				ast = create_ast_command_redir(root);
				final = create_final_ast(ast);
				ft_free_before_final_ast(&ast);
				final_expand(final);
				final_env = transform_env_in_double_tab(mini_env);
				executor(final, final_env);
				free_env(&mini_env);
				mini_env = copy_env(final_env);
				ft_free(NULL, &root, &src,&info);
				ft_free_final_ast(&final);
				//free_final_env(&final_env);
			}
			else
				ft_free(NULL, &root, &src,&info);
		}
			else (free(input));
	}
}


// faire ctrl c fait rien
// faire ctr D -> quitte le shell
// faire ctrl \ -> ne fait rien
// regler les invalid write, conditionnal jump
//faire norminette

//signaux 
	// qund jsuis dans la boucle while
	// qund jsuis dans un fork (genre dans mon cat)
	// qund jsuis dans le heredoc
// etre a laffut de tous les exit status

/*
imoumini@e1r10p21:~/42_cursus/minishell$ echo "$USER"
imoumini
imoumini@e1r10p21:~/42_cursus/minishell$ echo '$USER'
$USER
imoumini@e1r10p21:~/42_cursus/minishell$ echo '"$USER"'
"$USER"
imoumini@e1r10p21:~/42_cursus/minishell$ echo "'"$USER"'"
'imoumini'
imoumini@e1r10p21:~/42_cursus/minishell$ echo "''$USER''"
''imoumini''
imoumini@e1r10p21:~/42_cursus/minishell$ echo "ok"$USER"dac"
okimouminidac
imoumini@e1r10p21:~/42_cursus/minishell$ echo "ok"'$USER'"dac"
ok$USERdac
imoumini@e1r10p21:~/42_cursus/minishell$ echo "ok"''$USER"''dac"
okimoumini''dac
imoumini@e1r10p21:~/42_cursus/minishell$ ""'$USER'""
$USER: command not found
imoumini@e1r10p21:~/42_cursus/minishell$ echo ""'$USER'""
$USER
imoumini@e1r10p21:~/42_cursus/minishell$ echo ""'$USER'""



LEAKS : echo mathieu 


double free : minishell>echo $$$USER$USER$USER$$

minishell>minishell>echo $$$USER$USER$USER$$

minishell>free(): double free detected in tcache 2
[4]    95705 IOT instruction (core dumped)  ./minishell

minishell>echo $$$USER$USER$USER$$
[Detaching after fork from child process 96276]
"{
free(): double free detected in tcache 2

Program received signal SIGABRT, Aborted.
__pthread_kill_implementation (no_tid=0, signo=6, threadid=140737350932288) at ./nptl/pthread_kill.c:44
44      ./nptl/pthread_kill.c: No such file or directory.
(gdb) bt
#0  __pthread_kill_implementation (no_tid=0, signo=6, threadid=140737350932288) at ./nptl/pthread_kill.c:44
#1  __pthread_kill_internal (signo=6, threadid=140737350932288) at ./nptl/pthread_kill.c:78
#2  __GI___pthread_kill (threadid=140737350932288, signo=signo@entry=6) at ./nptl/pthread_kill.c:89
#3  0x00007ffff7d68476 in __GI_raise (sig=sig@entry=6) at ../sysdeps/posix/raise.c:26
#4  0x00007ffff7d4e7f3 in __GI_abort () at ./stdlib/abort.c:79
#5  0x00007ffff7daf6f6 in __libc_message (action=action@entry=do_abort, fmt=fmt@entry=0x7ffff7f01b8c "%s\n")
    at ../sysdeps/posix/libc_fatal.c:155
#6  0x00007ffff7dc6d7c in malloc_printerr (str=str@entry=0x7ffff7f04710 "free(): double free detected in tcache 2")
    at ./malloc/malloc.c:5664
#7  0x00007ffff7dc912b in _int_free (av=0x7ffff7f3fc80 <main_arena>, p=0x5555555a2ed0, have_lock=0)
    at ./malloc/malloc.c:4473
#8  0x00007ffff7dcb4d3 in __GI___libc_free (mem=<optimized out>) at ./malloc/malloc.c:3391
#9  0x000055555555bfe1 in free_final_env (tab_env=0x7fffffffd940) at ft_free/ft_free.c:92
#10 0x0000555555555901 in main (argc=1, argv=0x7fffffffdba8, env=0x7fffffffdbb8) at main.c:92


TON MINISHELL
minishell>export a="mathieu gruson"
minishell>echo $a
mathieu

BASH
minishell>export a="mathieu gruson"
minishell>echo $a
mathieu

BASH
imoumini@e2r9p11:~/minishell_imrane$ cat << "$USER"
> $HOME
> $USER
$HOME
MINISHELL
minishell>cat << "$USER"
> $HOME
> $USER
/mnt/nfs/homes/imoumini

BASH (qd on fait control D)
imoumini@e2r9p11:~/minishell_imrane$ ^C
imoumini@e2r9p11:~/minishell_imrane$ 
exit
imoumini@e2r9p11:~/minishell_imrane$ echo $?
130
MINISHELL
minishell>^C
minishell>
exit
➜  minishell_imrane git:(master) ✗ echo $?
0




COMMAND :
gdb
file ./minishell
run
=> tape les commandes que tu veux, si ca segfault voir commande si dessous 
bt

BASH
imoumini@e2r9p11:~/minishell_imrane$ echo -nnnnnnnnnnnnnn matheu
matheuimoumini@e2r9p11:~/minishell_imrane$ 
MINISHELL
minishell>echo -nnnnnnnnnnnnnnnnnnnnnnnnnnn matheiu
-nnnnnnnnnnnnnnnnnnnnnnnnnnn matheiu



==79096== 4,277 bytes in 69 blocks are still reachable in loss record 69 of 83
==79096==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==79096==    by 0x10B631: ft_strcpy (manip_env.c:25)
==79096==    by 0x10CAA2: copy_original_to_mini (manip_env7.c:41)
==79096==    by 0x10B9C8: copy_env (manip_env2.c:60)
==79096==    by 0x1098B9: main (main.c:85)

==79096== 3,379 bytes in 69 blocks are still reachable in loss record 57 of 83
==79096==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==79096==    by 0x10C79E: create_var_value (manip_env6.c:30)
==79096==    by 0x10CA53: create_var_name_and_value (manip_env7.c:32)
==79096==    by 0x10B9DC: copy_env (manip_env2.c:62)
==79096==    by 0x1098B9: main (main.c:85)

==79096== 2,144 bytes in 67 blocks are still reachable in loss record 55 of 83
==79096==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==79096==    by 0x10B774: new_node_env (manip_env.c:63)
==79096==    by 0x10B81F: add_node_env (manip_env.c:89)
==79096==    by 0x10B999: copy_env (manip_env2.c:55)
==79096==    by 0x1098B9: main (main.c:85)

==79096== 1,024 bytes in 1 blocks are still reachable in loss record 51 of 83
==79096==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==79096==    by 0x114B07: ft_calloc (in /mnt/nfs/homes/imoumini/minishell_imrane/minishell)
==79096==    by 0x10A301: init_buf_size (manipulate_token3.c:47)
==79096==    by 0x109D19: tokenize (manipulate_token.c:54)
==79096==    by 0x10AA55: parse_simple_command (parser.c:74)
==79096==    by 0x1096EA: main (main.c:65)

==79096== 967 bytes in 69 blocks are still reachable in loss record 42 of 83
==79096==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==79096==    by 0x10B88C: create_var_name (manip_env2.c:26)
==79096==    by 0x10CA47: create_var_name_and_value (manip_env7.c:31)
==79096==    by 0x10B9DC: copy_env (manip_env2.c:62)
==79096==    by 0x1098B9: main (main.c:85)


==79096== 96 bytes in 2 blocks are still reachable in loss record 33 of 83
==79096==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==79096==    by 0x10A882: new_node (parser.c:19)
==79096==    by 0x10AB19: if_tok_exist (parser.c:99)
==79096==    by 0x10AA1B: parse_simple_command (parser.c:70)
==79096==    by 0x1096EA: main (main.c:65)

==94331== 32 bytes in 1 blocks are still reachable in loss record 21 of 86
==94331==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==94331==    by 0x10B774: new_node_env (manip_env.c:63)
==94331==    by 0x10B81F: add_node_env (manip_env.c:89)
==94331==    by 0x109731: main (main.c:68)
==94331== 
==94331== 32 bytes in 1 blocks are still reachable in loss record 22 of 86
==94331==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==94331==    by 0x10B948: copy_env (manip_env2.c:47)
==94331==    by 0x1098B9: main (main.c:85)

==79096== 48 bytes in 1 blocks are still reachable in loss record 28 of 83
==79096==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==79096==    by 0x10A882: new_node (parser.c:19)
==79096==    by 0x10A9B4: parse_simple_command (parser.c:61)
==79096==    by 0x1096EA: main (main.c:65)

==94331== 2 bytes in 1 blocks are still reachable in loss record 1 of 86
==94331==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==94331==    by 0x114C7C: ft_itoa (in /mnt/nfs/homes/imoumini/minishell_imrane/minishell)
==94331==    by 0x109754: main (main.c:70)
==94331== 
==94331== 2 bytes in 1 blocks are still reachable in loss record 2 of 86
==94331==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==94331==    by 0x10B631: ft_strcpy (manip_env.c:25)
==94331==    by 0x10978B: main (main.c:71)

==94331== 32 bytes in 1 blocks are still reachable in loss record 20 of 86
==94331==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
==94331==    by 0x109AE9: init_src (init_src_token.c:19)
==94331==    by 0x10A996: parse_simple_command (parser.c:59)
==94331==    by 0x1096EA: main (main.c:65)

*/