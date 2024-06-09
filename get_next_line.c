/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:24:22 by jcohen            #+#    #+#             */
/*   Updated: 2024/06/09 15:58:50 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_get_line(char *stash, int index)
{
	char	*line;

	if (index == -1)
		index = ft_strlen(stash);
	line = malloc(index + 1);
	if (!line)
		return (NULL);
	line = ft_strncpy(line, stash, index);
	line[index] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*stash;
	char		*line;
	int			index;
	int			nb_carac;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	nb_carac = 1;
	index = -1;
	while (nb_carac > 0 && index == -1)
	{
		nb_carac = read(fd, buffer, BUFFER_SIZE);
		if (nb_carac < 0)
			return (NULL);
		buffer[nb_carac] = '\0';
		stash = ft_strjoin(stash, buffer);
		index = ft_strchr(stash, '\n');
	}
	if (nb_carac == 0 && stash[0] == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_get_line(stash, index);
	stash = ft_cleanstash(stash, index);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("gnl.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s$\n", line);
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}
