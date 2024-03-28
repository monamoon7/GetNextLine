/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_bonus.h                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mona <mona@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/03/15 15:47:58 by mona          #+#    #+#                 */
/*   Updated: 2024/03/28 18:00:36 by moshagha      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

int		ft_strlen(const char *str);
char	*ft_strchr(const char *str, int i);
char	*ft_strjoin(char *s1, char *s2);
char	*get_next_line(int fd);
char	*ft_free(char **buffer);

#endif