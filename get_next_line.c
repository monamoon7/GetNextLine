/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mona <mona@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 15:35:36 by mona          #+#    #+#                 */
/*   Updated: 2024/03/27 19:18:59 by moshagha      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	ft_free(char **buffer)
{
	if (!buffer)
		return ;
	if (*buffer)
		free(*buffer);
	*buffer = NULL;
}

char	*ft_line(char *remaining)
{
	int		i;
	char	*line;

	i = 0;
	if (!remaining || !remaining[0])
		return (NULL);
	while (remaining[i] && remaining[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + (remaining[i] == '\n') + 1));
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
	if (!remaining || !remaining[i])
	{
		ft_free(&remaining);
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
	ft_free(&remaining);
	return (new_remaining);
}

char	*read_and_collect(int fd, char *collect)
{
	char	*buffer;
	int		bytes;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (ft_free(&collect), NULL);
	if (!collect)
		collect = ft_strdup("");
	bytes = 1;
	while (!ft_strchr(collect, '\n') && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes > 0)
		{
			buffer[bytes] = '\0';
			collect = ft_strjoin(collect, buffer);
			if (collect == NULL)
				return (ft_free(&buffer), NULL);
		}
	}
	ft_free (&buffer);
	if (bytes == -1)
		return (ft_free(&collect), NULL);
	return (collect);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*collect;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	collect = read_and_collect(fd, collect);
	if (!collect || !collect[0])
		return (ft_free(&collect), NULL);
	line = ft_line(collect);
	collect = update_remaining(collect);
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;

// 	fd = open("a", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("ERROR OPENING FILE!\n");
// 		return (1);
// 	}
// 	line = get_next_line(fd);
// 	while (line != NULL)
// 	{
// 		printf("here\n");
// 		printf(">%s<", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	close(fd);
// 	fd = open("extra", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		printf("TEST\n");
// 		printf("ERROR OPENING FILE!\n");
// 		return (1);
// 	}
// 	line = get_next_line(fd);
// 		while (line != NULL)
// 	{
// 		printf("here\n");
// 		printf(">%s<", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// 	return (0);
// }
