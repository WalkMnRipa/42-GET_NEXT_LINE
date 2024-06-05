/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:24:22 by jcohen            #+#    #+#             */
/*   Updated: 2024/06/05 12:25:37 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*buffer[BUFFER_SIZE + 1];
	char	*stash;
	char	*new_stash;
	int		index;
	char	*line;
	int		nb_carac;

	if (fd < 0 && BUFFER_SIZE <= 0)
		return (NULL);
	nb_carac = read(fd, buffer, BUFFER_SIZE);
	if (nb_carac == -1)
		return (NULL);
	while (nb_carac > 0)
	{
		// remplit stash
		new_stash = ft_strjoin(buffer, stash);
		free(stash);
		stash = new_stash;
		index = ft_strchr(stash, '\n');
		if (index > -1)
			break ;
		free(buffer);
		nb_carac = read(fd, buffer, BUFFER_SIZE);
	}
	if (nb_carac == 0 && !stash)
		return (NULL);
	if (index == -1)
		index = ft_strlen(stash);
	line = malloc(index + 1);
	if (!line)
		return (NULL);
	line = ft_strncpy(line, stash, index);
	ft_clean_stash(stash, index);
	return (line);
}
