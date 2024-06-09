/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:24:22 by jcohen            #+#    #+#             */
/*   Updated: 2024/06/09 18:04:26 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_and_join(int fd, char *stash, int *nb_carac, int *index)
{
	char	buffer[BUFFER_SIZE + 1];
	int		read_result;

	read_result = read(fd, buffer, BUFFER_SIZE);
	if (read_result < 0)
		return (NULL);
	buffer[read_result] = '\0';
	stash = ft_strjoin(stash, buffer);
	*nb_carac = read_result;
	*index = ft_strchr(stash, '\n');
	return (stash);
}

char	*initialize_stash(int fd, char *stash)
{
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
	{
		stash = malloc(1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	return (stash);
}

char	*reset_if_empty(char *stash, int nb_carac)
{
	if (nb_carac == 0 && stash[0] == '\0')
	{
		free(stash);
		return (NULL);
	}
	return (stash);
}

char	*ft_extract_line(char *stash, int index)
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
	static char	*stash;
	char		*line;
	int			index;
	int			nb_carac;

	stash = initialize_stash(fd, stash);
	if (!stash)
		return (NULL);
	nb_carac = 1;
	index = -1;
	while (nb_carac > 0 && index == -1)
	{
		stash = ft_read_and_join(fd, stash, &nb_carac, &index);
		if (!stash)
			return (NULL);
	}
	stash = reset_if_empty(stash, nb_carac);
	if (!stash)
		return (NULL);
	line = ft_extract_line(stash, index);
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
		printf("%s$", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
