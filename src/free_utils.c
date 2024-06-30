/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 11:00:25 by mafranco          #+#    #+#             */
/*   Updated: 2024/06/29 11:00:28 by mafranco         ###   ########.fr       */
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
	if (w1->img->pathn)
		free(w1->img->pathn);
	if (w1->img->paths)
		free(w1->img->paths);
	if (w1->img->pathe)
		free(w1->img->pathe);
	if (w1->img->pathw)
		free(w1->img->pathw);
}

int	endbefore(t_data *w1, char *str)
{
	mlx_destroy_image(w1->mlx, w1->img->n);
	mlx_destroy_image(w1->mlx, w1->img->s);
	mlx_destroy_image(w1->mlx, w1->img->e);
	mlx_destroy_image(w1->mlx, w1->img->we);
	free_img_str(w1);
	free(w1->path);
	freeall(w1->table, w1->width);
	mlx_destroy_display(w1->mlx);
	free(w1->mlx);
	ft_putstr_fd(str, 2);
	return (1);
}

int	end(t_data *w1, char *str, int i)
{
	mlx_destroy_image(w1->mlx, w1->img->n);
	mlx_destroy_image(w1->mlx, w1->img->s);
	mlx_destroy_image(w1->mlx, w1->img->e);
	mlx_destroy_image(w1->mlx, w1->img->we);
	mlx_destroy_window(w1->mlx, w1->win);
	mlx_destroy_display(w1->mlx);
	free_img_str(w1);
	free(w1->img);
	freeall(w1->table, w1->width);
	free(w1->path);
	if (i == 1)
	{
		ft_putstr_fd(str, 2);
		return (1);
	}
	free(w1->mlx);
	ft_printf("%s", str);
	return (0);
}
