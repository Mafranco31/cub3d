/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:59:46 by mafranco          #+#    #+#             */
/*   Updated: 2024/06/29 10:59:47 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

static void	echappressed(t_data *w1)
{
	end(w1, "Echap pressed: end of the game\n", 0);
	exit(0);
}

void	moove(int x, char **t, int z, t_data *w1)
{
	int		i;
	double	v;
	double	w;
	int		s;

	s = w1->size;
	v = w1->dy * x;
	w = w1->dx * x;
	i = 1;
	if (t[(int)(w1->y + v * z) / s][(int)(w1->x + w * z) / s] != 49)
	{
		while (i < z && (t[(int)(w1->y + v * i) / s]
			[(int)(w1->x + w * i) / s] != 49)
		&& (t[((int)(w1->y + v * i) - 2) / s][((int)(w1->x + w * i)) / s] != 49)
		&& (t[((int)(w1->y + v * i)) / s][((int)(w1->x + w * i) - 2) / s] != 49)
		&& (t[((int)(w1->y + v * i) - 2) / s]
			[((int)(w1->x + w * i) - 2) / s] != 49))
			i++;
		w1->ly = w1->y;
		w1->lx = w1->x;
		w1->y += w1->dy * x * i;
		w1->x += w1->dx * x * i;
	}
}

void	moove_sides(int x, t_data *w1)
{
	int	i;
	int	vx;

	vx = x * w1->speed;
	i = 1;
	if (w1->table[(int)(w1->y + w1->dx * vx) / w1->size]
		[(int)(w1->x + -w1->dy * vx) / w1->size] != 49)
	{
		while (i < w1->speed
			&& (w1->table[(int)(w1->y + w1->dx * x * (i + 3)) / w1->size]
			[(int)(w1->x + -w1->dy * x * (i + 3)) / w1->size] != 49))
			i++;
		w1->ly = w1->y;
		w1->lx = w1->x;
		w1->y += w1->dx * x * i;
		w1->x += -w1->dy * x * i;
	}
}

void	rotate(float d, t_data *w1)
{
	w1->la = w1->a;
	w1->a += d;
	if (w1->a < 0)
		w1->a += 2 * PI;
	if (w1->a > 2 * PI)
		w1->a -= 2 * PI;
	w1->ldx = w1->dx;
	w1->ldy = w1->dy;
	w1->dx = cos(w1->a);
	w1->dy = sin(w1->a);
}

int	presskey(int kcode, t_data *w1)
{
	if (kcode == 65307)
		echappressed(w1);
	else if (kcode == 119)
		moove(1, w1->table, w1->speed, w1);
	else if (kcode == 65362)
		moove(1, w1->table, w1->speed, w1);
	else if (kcode == 115)
		moove(-1, w1->table, w1->speed, w1);
	else if (kcode == 65364)
		moove(-1, w1->table, w1->speed, w1);
	else if (kcode == 100)
		moove_sides(1, w1);
	else if (kcode == 97)
		moove_sides(-1, w1);
	else if (kcode == 65361)
		rotate(-w1->rotate_speed, w1);
	else if (kcode == 65363)
		rotate(w1->rotate_speed, w1);
	else
		ft_printf("Press W.A.S.D to play\n");
	print_view(w1);
	return (0);
}
