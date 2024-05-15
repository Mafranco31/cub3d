/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:57:36 by mafranco          #+#    #+#             */
/*   Updated: 2023/09/18 20:23:34 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

int	endbefore(t_data *w1, char *str)
{
	freeall(w1->table, w1->width);
	free(w1->path);
	ft_printf("Error\n%s\n", str);
	return (1);
}

int	end(t_data *w1, char *str, int i)
{
	mlx_destroy_image(w1->mlx, w1->img.dog);
	mlx_destroy_image(w1->mlx, w1->img.kennel);
	mlx_destroy_image(w1->mlx, w1->img.grass);
	mlx_destroy_image(w1->mlx, w1->img.fence);
	mlx_destroy_image(w1->mlx, w1->img.hotdog);
	mlx_destroy_window(w1->mlx, w1->win);
	freeall(w1->table, w1->width);
	free(w1->path);
	if (i == 1)
	{
		ft_printf("Error\n%s\n", str);
		return (1);
	}
	ft_printf("%s\n", str);
	return (0);
}

static int	moovedog(t_data *w1, int dx, int dy, int x)
{
	int	y;

	x = w1->img.dogx + dx;
	y = w1->img.dogy + dy;
	if (w1->table[y][x] == '1')
		return (0);
	if (w1->table[y][x] == 'C')
		w1->count--;
	if (w1->table[y][x] == 'E')
	{
		if (w1->count > 0)
			return (0);
		else
			return (1);
	}
	mlx_put_image_to_window(w1->mlx, w1->win,
		w1->img.grass, w1->img.dogx * 45, w1->img.dogy * 45);
	mlx_put_image_to_window(w1->mlx, w1->win, w1->img.dog, x * 45, y * 45);
	w1->table[y][x] = 'P';
	w1->table[w1->img.dogy][w1->img.dogx] = '0';
	w1->img.dogx = x;
	w1->img.dogy = y;
	w1->moove++;
	ft_printf("%d\n", w1->moove);
	return (0);
}

static void	echappressed(t_data *w1)
{
	end(w1, "ECHAP PRESSED = END OF GAME", 0);
	exit(0);
}

int	presskey(int kcode, t_data *w1)
{
	int	i;

	i = 0;
	if (kcode == 65307)
		echappressed(w1);
	if (kcode == 119)
		i += moovedog(w1, 0, -1, 0);
	else if (kcode == 97)
		i += moovedog(w1, -1, 0, 0);
	else if (kcode == 115)
		i += moovedog(w1, 0, 1, 0);
	else if (kcode == 100)
		i += moovedog(w1, 1, 0, 0);
	else
		ft_printf("PRESS W.A.S.D TO PLAY\n");
	if (i == 1)
	{
		w1->moove++;
		ft_printf("%d\n", w1->moove);
		end(w1, "YOU WIN !", 0);
		exit(0);
	}
	return (0);
}
