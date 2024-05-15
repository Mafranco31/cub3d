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
	//printf("i == %d, j == %d\n", i, j);
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
	//		printf("test\n");
			if (table[i][j] != 49 && table[i][j] != 32)//do with N, S, W, E too
			{
	//			printf("atest\n");
				if (check_around(w1, table, i, j) == 1)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

/*static int	checklen(char **table)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (table[0][i])
		i++;
	j = 1;
	while (table[j])
	{
		k = 0;
		while (table[j][k])
			k++;
		if (k != i)
			return (1);
		j++;
	}
	return (0);
}*/

int	checkmap(t_data *w1)
{
	//if (checklen(w1->table) == 1)
	//	return (endbefore(w1, "MAP IS NOT RECTANGULAR"));
	if (checkborder(w1, w1->table) == 1)
		return (endbefore(w1, "MAP SHOULD HAVE FENCE IN BORDERS"));
	return (initmap(w1, 0));
}
