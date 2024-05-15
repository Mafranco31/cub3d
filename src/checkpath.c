/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkpath.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:57:23 by mafranco          #+#    #+#             */
/*   Updated: 2023/09/18 20:32:36 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

static int	checkgete(char **table, int y, int x, t_data *w1)
{
	int	dx;
	int	dy;

	dx = w1->img.dogx;
	dy = w1->img.dogy;
	table[y][x] = '1';
	if (x == dx && y == dy)
		return (0);
	if (table[y + 1][x] != '1')
		if (checkgete(table, y + 1, x, w1) == 0)
			return (0);
	if (table[y - 1][x] != '1')
		if (checkgete(table, y - 1, x, w1) == 0)
			return (0);
	if (table[y][x + 1] != '1')
		if (checkgete(table, y, x + 1, w1) == 0)
			return (0);
	if (table[y][x - 1] != '1')
		if (checkgete(table, y, x - 1, w1) == 0)
			return (0);
	return (1);
}

static int	checkgetc(char **table, int y, int x, t_data *w1)
{
	int	dx;
	int	dy;

	dx = w1->img.dogx;
	dy = w1->img.dogy;
	table[y][x] = '1';
	if (x == dx && y == dy)
		return (0);
	if (table[y + 1][x] != '1' && table[y + 1][x] != 'E')
		if (checkgetc(table, y + 1, x, w1) == 0)
			return (0);
	if (table[y - 1][x] != '1' && table[y - 1][x] != 'E')
		if (checkgetc(table, y - 1, x, w1) == 0)
			return (0);
	if (table[y][x + 1] != '1' && table[y][x + 1] != 'E')
		if (checkgetc(table, y, x + 1, w1) == 0)
			return (0);
	if (table[y][x - 1] != '1' && table[y][x - 1] != 'E')
		if (checkgetc(table, y, x - 1, w1) == 0)
			return (0);
	return (1);
}

static void	searchdog(t_data *w1)
{
	int	x;
	int	y;

	y = 1;
	while (w1->table[y])
	{
		x = 1;
		while (w1->table[y][x])
		{
			if (w1->table[y][x] == 'P')
			{
				w1->img.dogx = x;
				w1->img.dogy = y;
				return ;
			}
		x++;
		}
	y++;
	}
}

int	checkpath(t_data *w1, int y, int x, int i)
{
	char	**copy;

	searchdog(w1);
	while (w1->table[y])
	{
		x = 1;
		while (w1->table[y][x])
		{
			if (w1->table[y][x] == 'C' || w1->table[y][x] == 'E')
			{
				copy = create1tab(w1);
				if (w1->table[y][x] == 'C')
					i = checkgetc(copy, y, x, w1);
				else if (w1->table[y][x] == 'E')
					i = checkgete(copy, y, x, w1);
				freeall(copy, w1->width);
				if (i == 1)
					return (1);
			}
			x++;
		}
		y++;
	}
	return (0);
}
