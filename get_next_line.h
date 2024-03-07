/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mona <mona@student.codam.nl>                 +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/01 15:25:15 by mona          #+#    #+#                 */
/*   Updated: 2024/03/08 00:36:39 by mona          ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef	GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

int	ft_strlen(const char *str);
char	*ft_strchr(const char *str, int i);
char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);

#endif