/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_and_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:57:36 by mafranco          #+#    #+#             */
/*   Updated: 2023/09/18 20:23:34 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

void	freeall(char **table, int i)
{
	while (i >= 0)
	{
		free(table[i]);
		i--;
	}	
	free(table);
}

void	free_img_str(t_data *w1)
{
	if (w1->img->pathN)
		free(w1->img->pathN);
	if (w1->img->pathS)
		free(w1->img->pathS);
	if (w1->img->pathE)
		free(w1->img->pathE);
	if (w1->img->pathW)
		free(w1->img->pathW);
	if (w1->img->pathTop)
		free(w1->img->pathTop);
	if (w1->img->pathBot)
		free(w1->img->pathBot);
}

int	endbefore(t_data *w1, char *str)
{
	freeall(w1->table, w1->width);
	free(w1->path);
	ft_putstr_fd(str, 2);
	free(w1->img);
	return (1);
}

int	end(t_data *w1, char *str, int i)
{
	mlx_destroy_image(w1->mlx, w1->img->N);
	mlx_destroy_image(w1->mlx, w1->img->S);
	mlx_destroy_image(w1->mlx, w1->img->E);
	mlx_destroy_image(w1->mlx, w1->img->W);
	mlx_destroy_window(w1->mlx, w1->win);
	free_img_str(w1);
	free(w1->img);
	freeall(w1->table, w1->width);
	free(w1->path);
	if (i == 1)
	{
		ft_putstr_fd(str, 2);
		return (1);
	}
	ft_printf("%s\n", str);
	return (0);
}

static void	echappressed(t_data *w1)
{
	end(w1, "ECHAP PRESSED = END OF GAME", 0);
	exit(0);
}

int	presskey(int kcode, t_data *w1)
{
	if (kcode == 65307)
		echappressed(w1);
	else
		ft_printf("PRESS W.A.S.D TO PLAY\n");
	return (0);
}
