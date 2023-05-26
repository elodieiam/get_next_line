/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elrichar <elrichar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:57:05 by elrichar          #+#    #+#             */
/*   Updated: 2023/05/26 13:07:38 by elrichar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean_stash(char *stash)
{
	char	*s;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free (stash);
		return (NULL);
	}
	s = malloc(sizeof(char) * (ft_strlen(stash) - i + 1));
	if (!s)
		return (NULL);
	i++;
	while (stash[i])
		s[j++] = stash[i++];
	s[j] = '\0';
	free (stash);
	return (s);
}

char	*get_line(char *stash)
{
	char	*s;
	int		i;

	i = 0;
	if (!stash[i]) //ce sont les deux lignes qui font tout foirer :s'il n'y a rien à récupérer dans stash pour line. 
		return (NULL);
	while (stash[i] && stash[i] != '\n')
		i++;
	s = malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
	{
		s[i] = stash[i];
		i++;
	}
	if (stash[i] == '\n')
	{
		s[i] = '\n';
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*read_file(int fd, char *stash)
{
	char	*buffer;
	int		read_bytes;

	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	read_bytes = 1;
	while ((!ft_strchr(stash, '\n')) && read_bytes != 0)
	{
		read_bytes = read(fd, buffer, BUFFER_SIZE);
		if (read_bytes == (-1))
		{
			free (buffer);
			return (NULL);
		}
		buffer[read_bytes] = '\0';
		stash = ft_strjoin(stash, buffer);
	}
	free (buffer);
	return (stash);
}

/* GNL : on stocke tout ce qui est lu par read dans stash,
on extrait line de end_line puis on nettoie stash
*/
char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_file(fd, stash);
	if (!stash)
		return (NULL);
	line = get_line(stash);
	stash = clean_stash(stash);
	return (line);
}
