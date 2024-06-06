/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcohen <jcohen@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 19:24:19 by jcohen            #+#    #+#             */
/*   Updated: 2024/06/06 18:03:32 by jcohen           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	len_str;

	len_str = 0;
	while (str[len_str])
		len_str++;
	return (len_str);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*join;
	int		i;
	int		j;

	if (!s1 || !s2)
		return (NULL);
	join = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!join)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		join[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		join[i + j] = s2[j];
		j++;
	}
	join[i + j] = '\0';
	free(s1);
	return (join);
}

// REGARDER DANS STASH SI IL Y A '\n'
// SI OUI, RETURN INDEX DU '\n'
int	ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

// EXTRAIRE LA LIGNE --> '\n'
// ft_strncpy (char *dest, char *src, int n) n etant l'index du '\n'

char	*ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

// NETTOYAGE DE STASH
// nettoyer le stash de la ligne extraite
/*
	stash = "bonjour\nsalut"
	buffer = "salut"
	index = 7
	Apres le passage de la fonction cleanstash, stash sera egal a "salut"
*/
char	*ft_cleanstash(char *stash, int index)
{
	char	*new_stash;
	int		i;
	int		j;

	new_stash = malloc(sizeof(char) * (ft_strlen(stash) - index + 1));
	if (!new_stash)
		return (NULL);
	i = index + 1;
	j = 0;
	while (stash[i])
	{
		new_stash[j] = stash[i];
		i++;
		j++;
	}
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}
