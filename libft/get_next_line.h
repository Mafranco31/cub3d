/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:59:15 by mafranco          #+#    #+#             */
/*   Updated: 2023/09/11 14:59:17 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

char	*my_malloc(size_t nbytes, size_t size);
char	*ft_substr(const char *total_buff, unsigned int start, size_t len);
char	*ft_strjoin(char *total_buff, char *tmp);
char	*fd_read(int fd, char *total_buff);
char	*take_line(char *total_buff);
char	*cut_static(char *total_buff);
char	*get_next_line(int fd);
char	*check_char(const char *str, int c);
size_t	ft_strlen(const char *str);

#endif
