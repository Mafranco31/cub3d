/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:58:20 by mafranco          #+#    #+#             */
/*   Updated: 2023/09/11 14:58:20 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*fd_read(int fd, char *total_buff)
{
	char	*tmp;
	int		chk;

	tmp = gnl_my_malloc(20, 1);
	if (!tmp)
		return (0);
	chk = 1;
	while (chk > 0 && !gnl_check_char(tmp, '\n'))
	{
		chk = read(fd, tmp, 20);
		if (chk > 0)
		{
			tmp [chk] = '\0';
			total_buff = gnl_strjoin(total_buff, tmp);
		}
	}
	free(tmp);
	if (chk == -1)
	{
		free(total_buff);
		return (0);
	}
	return (total_buff);
}

static char	*take_line(char *total_buff)
{
	char	*rtrn_buff;
	size_t	size;

	size = 0;
	if (!total_buff[0])
		return (0);
	while (total_buff[size] != '\n' && total_buff[size] != '\0')
		size++;
	if (total_buff[size] == '\n')
		rtrn_buff = gnl_substr(total_buff, 0, size + 1);
	else
		rtrn_buff = gnl_substr(total_buff, 0, size);
	return (rtrn_buff);
}

static char	*cut_static(char *total_buff)
{
	size_t	i;
	char	*new_total_buff;

	i = 0;
	while (total_buff[i] != '\n' && total_buff[i] != '\0')
		i++;
	if (total_buff[i] == '\n' && total_buff[i + 1] != '\0')
	{
		i++;
		new_total_buff = gnl_substr(total_buff, i,
				(gnl_strlen(total_buff) - i));
	}
	else
		new_total_buff = NULL;
	free (total_buff);
	if (!new_total_buff)
		return (NULL);
	return (new_total_buff);
}

char	*get_next_line(int fd)
{
	static char	*total_buff;
	char		*return_buff;

	if (!total_buff || (total_buff && !(gnl_check_char(total_buff, '\n'))))
		total_buff = fd_read(fd, total_buff);
	if (!total_buff)
		return (0);
	return_buff = take_line(total_buff);
	if (!return_buff)
	{
		free(total_buff);
		return (0);
	}
	total_buff = cut_static(total_buff);
	return (return_buff);
}
