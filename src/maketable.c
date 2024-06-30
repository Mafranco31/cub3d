/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maketable.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:59:17 by mafranco          #+#    #+#             */
/*   Updated: 2024/06/29 10:59:19 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

static int	maketable3(t_data *w1, char *line, int i, char *buf)
{
	if (buf)
		free(buf);
	if (w1->len_file > 1333333)
	{
		free(line);
		ft_putstr_fd("Error\nFor memory reason, we accept maps \
that are at maximum 1 000 000 cases\n", 2);
		return (0);
	}
	w1->table = ft_split(line, '\n');
	free(line);
	if (!w1->table)
	{
		ft_putstr_fd("Error\nMalloc failed in: maketable\n", 2);
		return (0);
	}
	if (i == 0)
		ft_putstr_fd("Error\nMap is empty\n", 2);
	return (i);
}

static int	maketable2(t_data *w1, int i, char *buf, int fd)
{
	char	*buf2;
	char	*line;

	buf2 = NULL;
	line = NULL;
	while (buf && ft_strchr(buf, 49) && w1->len_file < 1333334)
	{
		w1->len_file += ft_strlen(buf);
		if (ft_strlen(buf) > (size_t)w1->lenght)
			w1->lenght = ft_strlen(buf);
		i++;
		buf2 = ft_strdup(line);
		free(line);
		line = ft_strjoin(buf2, buf);
		free(buf);
		free(buf2);
		if (line == NULL)
		{
			ft_putstr_fd("Error\nMalloc failed in: maketable\n", 2);
			return (0);
		}
		buf = get_next_line(fd);
	}
	return (maketable3(w1, line, i, buf));
}

int	maketable(t_data *w1, int fd)
{
	char	*buf;

	w1->len_file = 0;
	buf = get_next_line(fd);
	if (!buf)
	{
		w1->table = NULL;
		ft_putstr_fd("Error\nMap is empty\n", 2);
		return (0);
	}
	while (buf && !ft_strchr(buf, 49))
	{
		if (ft_strlen(buf) > 1 && !ft_isspace(buf))
			return (err_msg_elements(buf, 1, 0));
		free(buf);
		buf = get_next_line(fd);
	}
	w1->lenght = ft_strlen(buf) - 1;
	return (maketable2(w1, 0, buf, fd));
}
