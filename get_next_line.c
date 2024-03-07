/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mona <mona@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 15:35:36 by mona          #+#    #+#                 */
/*   Updated: 2024/03/08 00:31:57 by mona          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_line(char *remaining)
{
	int		i;
	char	*line;

	i = 0;
	if (!emaining(i))
		return (NULL);
	while (remaining[i] && remaining[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (remaining[i] && remaining[i] != '\n')
	{
		line[i] = remaining[i];
		i++;
	}
	if (remaining[i] == '\n')
	{
		line[i] = remaining[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*update_remaining(char *remaining)
{
	int		i;
	int		new_start;
	char	*new_remaining;

	i = 0;
	while (remaining[i] && remaining[i] != '\n')
		i++;
	if (!remaining[i])
	{
		free (remaining);
		return (NULL);
	}
	new_remaining = (char *)malloc(sizeof(char) * (ft_strlen(remaining) - i + 1));
	if (!new_remaining)
		return (NULL);
	i++;
	new_start = 0;
	while (remaining[i])
		new_remaining[new_start++] = remaining[i++];
	new_remaining[new_start] = '\0';
	free (remaining);
	return (new_remaining);
}

char	*read_and_collect(int fd, char *collect)
{
	char	*buffer;
	int		bytes;
	char	*temp;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(collect, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buffer);
			free(collect);
			return (NULL);
		}
		buffer[bytes] = '\0';
		temp = collect;
		collect = ft_strjoin(collect, buffer);
		free (temp);
	}
	free (buffer);
	return (collect);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*collect;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	collect = read_and_collect(fd, collect);
	if (!collect)
		return (NULL);
	line = ft_line(collect);
	collect = update_remaining(collect);
	return (line);
}