/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   decoupe_ast_no_quotes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/11 20:31:15 by imrane            #+#    #+#             */
/*   Updated: 2023/03/27 13:54:23 by wcista           ###   ########.fr       */
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
	
	save_ast = NULL;
	if (!root)
		return (NULL);
	ptr = root -> first_child;
	i = 0;
	nbr_pipe = how_much_pipe(root);
	if (nbr_pipe > 0)
	{
		ast = malloc(sizeof(t_com *) * ((nbr_pipe + 1) + 1));
		ast[(nbr_pipe + 1)] = NULL;
	}
	else
	{
		ast = malloc(sizeof(t_com *) + 1);
		ast[1] = NULL;
		nbr_pipe = 1;
	}

	// c vers la que je dois free save ast sans que ca nike ma logique
	// jvai creer une valeur de save 
	// jvai passer le vrai a la fonction puis free la valeur de save
	// voir le moment opportun pour free 
	while (nbr_pipe >= 0)
	{
		if (save_ast)
			save_ast = isolate_command_redir(save_ast -> save_ptr);
		else
			save_ast = isolate_command_redir(ptr);
		
		if (save_ast)
		{
			if (save_ast -> command)
				ast[i] = save_ast -> command;
			else
			{
				ast[i] = malloc(sizeof(t_com));
				ast[i] -> txt = NULL;
			}
			if (ast[i])
				ast[i] -> redir = save_ast -> redir;
			free(save_ast);
			i++;
		}
		// c ici quon free lancien save ast
		nbr_pipe--;
	}
	return (ast);
}

// qund je met juste < sans rien avant ca fonctionne pas
// il me compte ni comme une redir ni l suite
// voir pk
// et en plus ca creer des leaks
// qund ca c regler voir les read bizzare
// une fois que c bon voit tous le stests sans parenthese
// puis faire logique parenthese et voir tous les test sans parentheses
t_ast *isolate_command_redir(t_node *ptr)
{
	
	t_ast  *save_ast;
	t_redir *redir;
	t_com	*com;

	if (!ptr)
		return (NULL);
	com = NULL;
	redir = NULL;
	if (ptr)
	{
		while (ptr && ft_stcmp(ptr -> txt, "|") != 1)
		{
			// decoupe la command et arguments
			while (ptr && ft_stcmp(ptr -> txt, "|") != 1 && ft_stcmp(ptr -> txt, "<") != 1 && ft_stcmp(ptr -> txt, ">") != 1)
			{
				com = create_com_node(com, ptr);
				ptr = ptr -> next_sibling;
			}
			if (ptr)
			{
				// ok ici en fait javance jusqua pipe
				// alors que jeverai avancer jusquau prochain truc et puis recommencer le processus
				
				if (ft_stcmp(ptr -> txt, "<") == 1 || ft_stcmp(ptr -> txt, ">") == 1 )
				{
						if ((ptr -> next_sibling  && ft_stcmp(ptr -> next_sibling -> txt, "<") == 1) || (ptr -> next_sibling  && (ft_stcmp(ptr -> next_sibling -> txt, ">") == 1 )))
						{
							if (ptr && ft_stcmp(ptr -> txt, "|") != 1)
								redir = create_redir_node(redir, ptr);
							if (ptr && ft_stcmp(ptr -> txt, "|") != 1)
								ptr = ptr -> next_sibling;
							if (ptr && ft_stcmp(ptr -> txt, "|") != 1)
								ptr = ptr -> next_sibling;
							if (ptr && ft_stcmp(ptr -> txt, "|") != 1)
								redir = create_redir_node(redir, ptr);
						}
						else if (ptr && ft_stcmp(ptr -> txt, "|") != 1)
						{
							if (ptr && ft_stcmp(ptr -> txt, "|") != 1)
								redir = create_redir_node(redir, ptr);
							if (ptr )
								ptr = ptr -> next_sibling;
	
							if (ptr && ft_stcmp(ptr -> txt, "|") != 1) 
								redir = create_redir_node(redir, ptr);
						}
						if (ptr && ft_stcmp(ptr -> txt, "|") != 1)
							ptr = ptr -> next_sibling;
				}
			}
		}
	// avance prochaine command
		if (ptr)
			ptr = ptr -> next_sibling;
		// sauvegarde debut prochainne command + redir + command
		save_ast = malloc(sizeof(save_ast));
		if (com)
			save_ast -> command = com;
		else
			save_ast -> command = NULL;
			
		if (redir)
			save_ast -> redir = redir;
		else
			save_ast -> redir = NULL;
			
		if (ptr)
			save_ast -> save_ptr = ptr;
	}
	return (save_ast);
}

void print_final_ast(t_com **ast)
{
	int i;
	i = 0;
	printf("c4.1\n");
	while(ast[i])
	{
		
		ft_printf("------------------------\n");
		printf("command %i is :\n", i);
		print_command(ast[i]);
		print_redir(ast[i] -> redir);
		ft_printf("------------------------\n");
		i++;
	}
}

void print_command(t_com *com)
{
	t_com *ptr;
	if (!com)
	{
		printf("there is nos command\n");
		return ;
	}
	ptr = com;
	while (ptr)
	{
		ft_printf("command is000 \n");
		ft_printf("%s\n",ptr -> txt);
		ptr = ptr -> next_sibling;
	}
}
void print_redir(t_redir *redir)
{
	t_redir *ptr;
	if (!redir)
	{
		ft_printf("there is no redir for this command\n");
		return ;
	}
	ptr = redir;
	while (ptr)
	{
		ft_printf("redir is \n");
		ft_printf("---00redir00---%s\n",ptr -> txt);
		ptr = ptr -> next_sibling;
	}
}

/*

< z1 ls < z2 > z3
ATTENTION : ls est une commande

l'oredre des in file ou outfile par arrport a la command importe peu, lui il regarde juste si ya un in file
 et il le prend comme arg, en fait c le in file en soit qui compte et non lordre darriver. par contre
 il ne prend que un in file et un file si yen a pusieurs ca bug pas mais
 il choisi celui qui a la plus grande prioriter
 et entre un argument et un in file il prend largument en premier
aussi ya des cmmand meme si tu leur psse un infile ca va pas buger mais elle vont lignrer parce que
elle prenne pas dargument comme ls par exemple
ne pas confondre un argument dune option , meme si au final dans execv les options ou argument sont au meme endroit
la command est assez intlligent pour ignorer les argument mme si tu lui en donne alors quelle en prend pas

l$EE ($EE vaut "l -sa")
doit donner "ls" "-a" et non "ls -a"

imoumini@e2r7p16:~/42_cursus/minishell$ ls > $EEEEEEEEE
bash: $EEEEEEEEE: ambiguous redirect

-> on recoit ca car $EEEEEEEEE n existe pas ds les variables d env ou si est vide ds la variable
imoumini@e2r7p16:~/42_cursus/minishell$ export FF=""
imoumini@e2r7p16:~/42_cursus/minishell$ ls > $FF
bash: $FF: ambiguous redirect
comme c'est vide, on essaie de rediriger vers un fichier inexistant et donc il faut mettre une erreur comme qd
on a "ls < < test" car on ne peut pas avoir un redirecteur vide"


gere : 
Entré vide -> ok 
Redirection a un seul argument et après peut y avoir une command et pas avoir une redir
Après une redir c un ficher mais seulement si c immédiat
Le dollars n'est pas un separateur ça doit juste remplacer, ex :l$EE = ls-a et après s'assurer que ls-a est bien séparé
Faut decouper après avoir expand
Ls < < z1 ça doot pas fonctionner car fien a la droite immédiate 
*/

/*

$USER$USER doit resulter en une string "imouminiimoumini" et non pas en "imoumini" "imoumini"
$$USER doit afficher 14098USER
echo $$ => 646654 (un chiffre)

si on ecrit un dollar seul, il ne faut pas expand


$Uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu => segfault pour un env inexistant, il faut remplacer 
par du vide. Ca revient a envoyer une string vide

minishell> "" => segfault aussi. car ca sera remplacer par du vide

env -i ./minishell =>  si je fait echo $HOME => ca segfault car avec env -i, ca enleve les variables d env,
donc il ny a plus de HOME
*/