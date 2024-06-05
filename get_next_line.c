/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:24:22 by jcohen            #+#    #+#             */
/*   Updated: 2024/06/05 18:02:57 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	static char	*stash = NULL;
	int			index;
	char		*line;
	int			nb_carac;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = strdup("");
	index = ft_strchr(stash, '\n');
	if (index == -1)
		nb_carac = read(fd, buffer, BUFFER_SIZE);
	else
		nb_carac = 0;
	if (nb_carac == -1)
		return (NULL);
	while (nb_carac > 0)
	{
		buffer[nb_carac] = '\0';
		stash = ft_strjoin(stash, buffer);
		index = ft_strchr(stash, '\n');
		if (index > -1)
			break ;
		nb_carac = read(fd, buffer, BUFFER_SIZE);
	}
	if (index == -1)
		index = ft_strlen(stash);
	line = malloc(index + 1);
	if (!line)
		return (NULL);
	line = ft_strncpy(line, stash, index);
	ft_cleanstash(stash, index);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*line;

	fd = open("ptheo.txt", O_RDONLY);
	line = get_next_line(fd);
	while (line)
	{
		printf("%s\n", line);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (0);
}
