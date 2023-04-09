/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcista <wcista@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 15:58:50 by wcista            #+#    #+#             */
/*   Updated: 2023/04/09 11:59:57 by wcista           ###   ########.fr       */
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	i;

	if (nmemb && ((nmemb * size / nmemb) != size))
		return (NULL);
	if (nmemb == 0 || size == 0)
	{
		nmemb = 1;
		size = 1;
	}
	i = 0;
	p = malloc(nmemb * size);
	if (p == NULL)
		return (NULL);
	while (i < nmemb * size)
	{
		((char *)p)[i] = '\0';
		i++;
	}
	return (p);
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
/* 	(void)ac;
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
	free(s); */

	int	**fd;

	fd = (int **)ft_calloc(sizeof(int *), 0);
	if (!fd)
		return (printf("MALLOC FAIL\n"), 1);
	else
		printf("MALLOC SUCCESS\n");
	free(fd);
	return (0);
}
