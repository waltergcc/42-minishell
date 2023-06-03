/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcorrea- <wcorrea-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 00:26:26 by wcorrea-          #+#    #+#             */
/*   Updated: 2023/04/27 00:22:02 by wcorrea-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*get_line(char **buffer)
{
	char	*line;
	char	*keep;
	size_t	til_null;
	size_t	til_new;

	til_new = strlen_at(*buffer, '\n');
	if ((*buffer)[til_new] == '\n')
		til_new++;
	line = cpy_buffer(*buffer, til_new);
	if (!line)
		return (NULL);
	til_null = strlen_at(*buffer, '\0');
	keep = cpy_buffer(*buffer + til_new, til_null - til_new + 1);
	if (!keep)
	{
		free (line);
		return (NULL);
	}
	free(*buffer);
	*buffer = keep;
	return (line);
}

static char	*get_current_buffer(int fd, char *buffer)
{
	char	*current;
	ssize_t	bytes;

	bytes = 1;
	current = (char *)malloc(BUFFER_SIZE + 1);
	if (!current)
		return (NULL);
	while (bytes > 0 && !find_chr(buffer, '\n'))
	{
		bytes = read(fd, current, BUFFER_SIZE);
		if (bytes == 0)
			break ;
		if (bytes == -1)
		{
			free(current);
			return (NULL);
		}
		current[bytes] = '\0';
		buffer = merge_previous_and_current(buffer, current);
	}
	free(current);
	if (strlen_at(buffer, '\0') > 0)
		return (buffer);
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*buffer[MAX_FILES];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FILES)
		return (NULL);
	buffer[fd] = get_current_buffer(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = get_line(&buffer[fd]);
	if (!buffer[fd][0])
	{
		free (buffer[fd]);
		buffer[fd] = NULL;
	}
	return (line);
}
