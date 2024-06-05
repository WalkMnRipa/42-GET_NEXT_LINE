/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:24:23 by jcohen            #+#    #+#             */
/*   Updated: 2024/06/05 14:53:56 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFFER_SIZE 42

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(char *str, char c);
char	*ft_strncpy(char *dst, char *src, int n);
void	ft_cleanstash(char *stash, int index);

char	*get_next_line(int fd);

#endif