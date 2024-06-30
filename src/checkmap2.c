/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:59:04 by mafranco          #+#    #+#             */
/*   Updated: 2024/06/29 10:59:06 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

static int	initmap2(t_data *w1, int *k, int i, int j)
{
	if (w1->table[i][j] == 78 || w1->table[i][j] == 83
		|| w1->table[i][j] == 69 || w1->table[i][j] == 87)
	{
		if (*k == 1)
			return (endbefore(w1, "Error\nOnly one starting position \
in the map is posible\n"));
		w1->startx = j;
		w1->starty = i;
		w1->startangle = w1->table[i][j];
		*k = 1;
	}
	else if (w1->table[i][j] != 48 && w1->table[i][j] != 49
		&& w1->table[i][j] != 32)
		return (endbefore(w1, "Error\nYou can only put 0 / 1 / N / S\
/ E / W in your map\n"));
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
			if (initmap2(w1, &k, i, j) == 1)
				return (1);
			j++;
		}
		i++;
	}
	if (k == 0)
		return (endbefore(w1, "Error\nMap needs a starting point as N / S\
/ E / W\n"));
	return (0);
}
