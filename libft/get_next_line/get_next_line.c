/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imoumini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 16:28:39 by imoumini          #+#    #+#             */
/*   Updated: 2022/07/10 16:28:44 by imoumini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int	is_end_of_line(char	*str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

void	put_extra_in_buff(char *savetext, char *buff)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (savetext[i] != '\0')
	{
		while ((savetext[i] != '\n') && (savetext[i] != '\0'))
			i++;
		if (savetext[i] == '\n')
		{
			i++;
			while (savetext[i] != '\0')
			{
				buff[j] = savetext[i];
				j++;
				i++;
			}
		}
		if (buff[j] != '\0')
			i++;
	}
}

void	line_to_return(char *buff)
{
	int		i;

	i = 0;
	while (buff[i] != '\0')
	{
		if ((buff[i] == '\n'))
		{
			i++;
			while (buff[i] != '\0')
			{
				buff[i] = '\0';
				i++;
			}
		}
		if (buff[i] != '\0')
			i++;
	}
}

int	is_empty(char *buff)
{
	int	i;

	i = 0;
	if (buff == NULL)
		return (1);
	if (buff[i] == '\0')
	{
		return (1);
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*savetext;
	int			nbr_of_bytes_read;

	savetext = NULL;
	if (is_empty(buff) == 0)
		savetext = ft_strjoin(savetext, buff);
	if ((fd < 0) || (BUFFER_SIZE <= 0) || (fd > 1024))
		return (NULL);
	while (is_end_of_line(buff) != 1)
	{
		nbr_of_bytes_read = read(fd, buff, BUFFER_SIZE);
		buff[nbr_of_bytes_read] = '\0';
		if (nbr_of_bytes_read == 0)
			return (savetext);
		if (nbr_of_bytes_read == -1)
			return (free(savetext), NULL);
		savetext = ft_strjoin(savetext, buff);
	}
	if (!savetext)
		return (NULL);
	erase_buff(buff);
	put_extra_in_buff(savetext, buff);
	line_to_return(savetext);
	return (savetext);
}

// int main(void)
// {
//     int fd;
// 	char *p;
// 	char c = 'c';
//     fd = open("text.txt", O_RDONLY);
// 	p = &c;
// 	while (p != NULL)
//     {
// 		p = get_next_line(fd);
// 		if (p != NULL)
// 		{
// 			printf("%s", p);
// 		}
// 		free(p);
// 	}
// 	close(fd);
// }