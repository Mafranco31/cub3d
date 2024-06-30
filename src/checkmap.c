/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkmap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:57:18 by mafranco          #+#    #+#             */
/*   Updated: 2024/06/11 10:35:56 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

static int	check_around2(char **t, int i, int j, int ret)
{
	if (t[i - 1][j - 1] == 13 || t[i - 1][j] == 13
		|| t[i - 1][j + 1] == 13)
		ret = 8;
	else if (t[i][j - 1] == 13 || t[i][j + 1] == 13)
		ret = 9;
	else if (t[i + 1][j - 1] == 13 || t[i + 1][j] == 13
		|| t[i + 1][j + 1] == 13)
		ret = 10;
	return (ret);
}

int	check_around(char **t, int i, int j)
{
	int	ret;

	ret = 0;
	if (i == 0 || j == 0)
		ret = 1;
	else if (!t[i - 1][j - 1] || !t[i - 1][j] || !t[i - 1][j + 1])
		ret = 2;
	else if (!t[i][j - 1] || !t[i][j + 1])
		ret = 3;
	else if (!t[i + 1][j - 1] || !t[i + 1][j] || !t[i + 1][j + 1])
		ret = 4;
	else if (t[i - 1][j - 1] == 32 || t[i - 1][j] == 32
		|| t[i - 1][j + 1] == 32)
		ret = 5;
	else if (t[i][j - 1] == 32 || t[i][j + 1] == 32)
		ret = 6;
	else if (t[i + 1][j - 1] == 32 || t[i + 1][j] == 32
		|| t[i + 1][j + 1] == 32)
		ret = 7;
	else
		ret = check_around2(t, i, j, ret);
	return (ret);
}

static int	checkborder(char **table)
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
				if (check_around(table, i, j) > 0)
					return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

int	checkmap(t_data *w1)
{
	if (checkborder(w1->table) > 0)
		return (endbefore(w1, "Error\nMap should have wall in border\n"));
	return (initmap(w1, 0));
}
