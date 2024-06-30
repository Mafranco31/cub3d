/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_view.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:59:23 by mafranco          #+#    #+#             */
/*   Updated: 2024/06/29 10:59:24 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

void	init_print_view(t_data *w1, t_view *view)
{
	view->x = 0;
	view->val_angle = (PI / 3) / w1->winl;
	view->angle = w1->a - (PI / 6);
	view->mapx = w1->x / w1->size;
	view->mapy = w1->y / w1->size;
	view->hit = 0;
	view->side = 0;
	w1->img1.img = mlx_new_image(w1->mlx, w1->winl, w1->winh);
	w1->img1.addr = mlx_get_data_addr(w1->img1.img, &w1->img1.bpp,
			&w1->img1.line_length, &w1->img1.endian);
}

void	print_view_side0(t_data *w1, t_view *view)
{
	view->dist = (view->side_distx - view->delta_distx);
	view->opposite = (int)(fabs(sin(view->angle) * view->dist));
	if (cos(view->angle) > 0)
	{
		view->texture = w1->img->e;
		if (sin(view->angle) < 0)
			view->wall_pos = w1->y - view->opposite;
		else
			view->wall_pos = w1->y + view->opposite;
	}
	else
	{
		view->texture = w1->img->we;
		if (sin(view->angle) > 0)
			view->wall_pos = w1->y + view->opposite;
		else
			view->wall_pos = w1->y - view->opposite;
	}
	view->img_pos = view->wall_pos % w1->size;
}

void	print_view_side1(t_data *w1, t_view *view)
{
	view->dist = (view->side_disty - view->delta_disty);
	view->opposite = (int)(fabs(cos(view->angle) * view->dist));
	if (sin(view->angle) > 0)
	{
		view->texture = w1->img->s;
		if (cos(view->angle) > 0)
			view->wall_pos = w1->x + view->opposite;
		else
			view->wall_pos = w1->x - view->opposite;
	}
	else
	{
		if (cos(view->angle) > 0)
			view->wall_pos = w1->x + view->opposite;
		else
			view->wall_pos = w1->x - view->opposite;
		view->texture = w1->img->n;
	}
	view->img_pos = view->wall_pos % w1->size;
}

int	print_view(t_data *w1)
{
	t_view	view;

	init_print_view(w1, &view);
	mlx_clear_window(w1->mlx, w1->win);
	while (view.x < w1->winl)
	{
		modif_print_view(w1, &view);
		if (view.side == 0)
			print_view_side0(w1, &view);
		else
			print_view_side1(w1, &view);
		draw_vertical_line(w1, view.dist * sin(view.final_angle),
			&view);
		view.angle += view.val_angle;
		view.x += 1;
	}
	mlx_put_image_to_window(w1->mlx, w1->win, w1->img1.img, 0, 0);
	mlx_destroy_image(w1->mlx, w1->img1.img);
	return (0);
}
