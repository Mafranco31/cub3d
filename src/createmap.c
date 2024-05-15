/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   createmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:57:27 by mafranco          #+#    #+#             */
/*   Updated: 2023/09/11 14:57:28 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

/*static	int	checkconst(t_data *w1, int nbE, int nbP)
{
	if (w1->count <= 0)
		return (endbefore(w1, "MAP NEED AT LEAST 1 C (hotdog)"));
	if (nbE != 1)
		return (endbefore(w1, "MAP NEED ONLY 1 E (kennel)"));
	if (nbP != 1)
		return (endbefore(w1, "MAP NEED ONLY 1 P (dog)"));
	return (0);
}*/

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
	//return (checkconst(w1, k, l));
}
