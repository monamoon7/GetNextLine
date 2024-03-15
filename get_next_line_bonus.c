/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mona <mona@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 15:47:30 by mona          #+#    #+#                 */
/*   Updated: 2024/03/15 17:46:05 by mona          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void ft_free(char **buffer)
{
	if (*buffer)
		free(*buffer);
	*buffer = NULL;
}

char	*ft_line(char *remaining)
{
	int		i;
	char	*line;

	i = 0;
	if (!remaining[i])
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
	new_remaining = (char *)malloc(sizeof(char)
			* (ft_strlen(remaining) - i + 1));
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
	if (!collect)
		collect = ft_strdup("");
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!ft_strchr(collect, '\n') && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
		{
			ft_free(&buffer);
			return (ft_free(&collect), NULL);
		}
		buffer[bytes] = '\0';
		temp = collect;
		collect = ft_strjoin(collect, buffer);
		ft_free (&temp);
	}
	ft_free (&buffer);
	return (collect);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*collect[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	collect[fd] = read_and_collect(fd, collect[fd]);
	if (!collect[fd] || !collect[fd][0])
		return (ft_free(&collect[fd]), NULL);
	line = ft_line(collect[fd]);
	collect[fd] = update_remaining(collect[fd]);
	return (line);
}

// int	main(void)
// {
// 	int		fd
// 	char	*line;

// 	fd = open("example.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("ERROR OPENING FILE!\n");
// 		return (1);
// 	}
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }

