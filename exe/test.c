/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:58:50 by wcista            #+#    #+#             */
/*   Updated: 2023/04/07 18:09:18 by wcista           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_exe.h"

void	ft_putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		write(fd, &s[i], 1);
		i++;
	}
}
void	print_perror(char *s)
{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(s, 2);
		ft_putstr_fd(": ", 2);
		perror("");
}

int	main(int ac, char **av)
{
	(void)ac;
	int	fd;
	int	fd2;
	char	*s;
	
	fd = open(av[1], O_RDONLY);
	fd2 = open(av[2], O_RDONLY);
	s = malloc(sizeof(char) * 10);
	if (fd == -1)
	{
		close(fd2);
		free(s);
		print_perror(av[1]);
		return (1);
	}
	print_perror(av[1]);
	close(fd);
	close (fd2);
	free(s);
	return (0);
}
