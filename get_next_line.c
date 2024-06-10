/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:24:22 by jcohen            #+#    #+#             */
/*   Updated: 2024/06/10 17:19:19 by jcohen           ###   ########.fr       */
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
	if (read_result == 0 && !stash)
		return (NULL);
	buffer[read_result] = '\0';
	stash = ft_strjoin(stash, buffer);
	if (!stash)
		return (NULL);
	*nb_carac = read_result;
	*index = ft_strchr(stash, '\n');
	return (stash);
}

char	*init_stash(int fd, char *stash)
{
	(void)fd;
	if (!stash)
	{
		stash = malloc(sizeof(char) * 1);
		if (!stash)
			return (NULL);
		stash[0] = '\0';
	}
	return (stash);
}

char	*reset_if_empty(char *stash, int nb_carac)
{
	if (!stash)
		return (NULL);
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

	if (!stash)
		return (NULL);
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
	static char	*stash = NULL;
	char		*line;
	int			index;
	char		*new_stash;
	int			nb_carac;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	free((nb_carac = 1, index = -1, stash = init_stash(fd, stash), NULL));
	if (!stash)
		return (NULL);
	while (nb_carac > 0 && index == -1)
	{
		new_stash = ft_read_and_join(fd, stash, &nb_carac, &index);
		if (!new_stash)
			return (free(stash), stash = NULL, NULL);
		stash = new_stash;
		if (nb_carac == 0 && stash[0] == '\0')
			free((stash = NULL, stash));
	}
	stash = reset_if_empty(stash, nb_carac);
	line = ft_extract_line(stash, index);
	if (!line)
		return (free(stash), stash = NULL, NULL);
	return (stash = ft_cleanstash(stash, index), line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("41_with_nl", O_RDONLY);
// 	line = get_next_line(fd);
// 	while (line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }
