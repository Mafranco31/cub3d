/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:57:18 by mafranco          #+#    #+#             */
/*   Updated: 2023/09/18 20:49:41 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

static	char	**maketable2(char **table, int fd)
{
	char	*buf2;
	char	*line;
	char	*buf;

	buf2 = NULL;
	line = NULL;
	buf = get_next_line(fd);
	while (buf)
	{
		buf2 = ft_strdup(line);
		free(line);
		line = ft_strjoin(buf2, buf);
		free(buf);
		free(buf2);
		if (line == NULL)
			return (NULL);
		buf = get_next_line(fd);
	}
	table = ft_split(line, '\n');
	free(line);
	return (table);
}

char	**create1tab(t_data *w1)
{
	char	**table;
	int		fd;

	table = NULL;
	fd = open(w1->path, O_RDONLY);
	if (fd == -1)
		return (NULL);
	table = maketable2(table, fd);
	close(fd);
	return (table);
}

int	check_around(t_data *w1, char **t, int i, int j)
{
	if (i == 0 || j == 0 || i == w1->width - 1 || j == w1->lenght - 1)// check if width is i and lenght is j
		return (1);
	if (!t[i - 1][j - 1] || !t[i - 1][j] || !t[i - 1][j + 1])
		return (1);
	if (!t[i][j - 1] || !t[i][j + 1])
		return (1);
	if (!t[i + 1][j - 1] || !t[i + 1][j] || !t[i + 1][j + 1])
		return (1);
	if (t[i - 1][j - 1] == 32 || t[i - 1][j] == 32 || t[i - 1][j + 1] == 32)
		return (1);
	if (t[i][j - 1] == 32 || t[i][j + 1] == 32)
		return (1);
	if (t[i + 1][j - 1] == 32 || t[i + 1][j] == 32 || t[i + 1][j + 1] == 32)
		return (1);
	return (0);
}

static int	checkborder(t_data *w1, char **table)
{
	int	i;
	int	j;

	i = 0;
	while (table[i])
	{
		j = 0;
		while (table[i][j])
		{
			if (table[i][j] != 49 && table[i][j] != 32)
			{
				if (check_around(w1, table, i, j) == 1)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	initmap(t_data *w1, int k)
{
	int	i;
	int	j;

	i = 0;
	while (w1->table[i])
	{
		j = 0;
		while (w1->table[i][j])
		{
			if (w1->table[i][j] == 78 || w1->table[i][j] == 83 || w1->table[i][j] == 69 || w1->table[i][j] == 87)
			{
				if (k == 1)
					return (endbefore(w1, "Only one starting position in the map is posible"));
				k = 1;
			}
			else if (w1->table[i][j] != 48 && w1->table[i][j] != 49 && w1->table[i][j] != 32)
				return (endbefore(w1, "You can only put 0 / 1 / N / S / E / W in your map"));
			j++;
		}
		i++;
	}
	if (k == 0)
		return (endbefore(w1, "Map needs the starting point as N / S / E / W"));
	return (0);
}

int	checkmap(t_data *w1)
{
	if (checkborder(w1, w1->table) == 1)
		return (endbefore(w1, "MAP SHOULD HAVE FENCE IN BORDERS"));
	return (initmap(w1, 0));
}
