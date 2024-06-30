/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_view2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:59:27 by mafranco          #+#    #+#             */
/*   Updated: 2024/06/29 10:59:29 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

void	my_mlx_pixel_put(t_test *test, int x, int y, int color)
{
	char	*dst;

	dst = test->addr + (y * test->line_length + x * (test->bpp / 8));
	*(unsigned int *)dst = color;
}

t_test	init_struct_draw(t_data *w1, int dist, void *texture, int pxl)
{
	t_test	test;

	test.img = texture;
	test.addr = mlx_get_data_addr(test.img,
			&test.bpp, &test.line_length, &test.endian);
	test.drawstart = -(int)((w1->size * 1950) / dist) / 2 + w1->winh / 2;
	test.drawposstart = test.drawstart;
	test.drawend = (int)((w1->size * 1950) / dist) / 2 + w1->winh / 2;
	if (test.drawstart < 0)
		test.drawstart = 0;
	if (test.drawend >= w1->winh)
		test.drawend = w1->winh - 1;
	test.draw = test.drawstart;
	test.i = 0;
	test.pxl = pxl;
	return (test);
}

void	draw_ceil_floor(t_test *t, t_data *w1, int c_f, t_test *img1)
{
	if (c_f == 0)
	{
		while (t->i < t->drawstart)
		{
			my_mlx_pixel_put(img1, t->pxl, t->i,
				(unsigned int)w1->img->color_top);
			t->i += 1;
		}
	}
	else
	{
		while (t->draw + 1 < w1->winh)
		{
			my_mlx_pixel_put(img1, t->pxl, t->draw,
				(unsigned int)w1->img->color_bot);
			t->draw++;
		}
	}
}

void	draw_vertical_line(t_data *w1, int dist, t_view *view)
{
	t_test	test;

	if (dist == 0)
		dist = 1;
	test = init_struct_draw(w1, dist, view->texture, view->x);
	draw_ceil_floor(&test, w1, 0, &w1->img1);
	while (test.draw < test.drawend)
	{
		if (test.drawposstart < 0)
			test.img_height_pos = (double)((test.draw + test.drawposstart * -1)
					* w1->img->h) / (test.drawposstart * -2 + w1->winh);
		else
			test.img_height_pos = (double)((test.draw - test.drawstart)
					* w1->img->h) / (double)(test.drawend - test.drawstart);
		test.dst = (unsigned int *)(test.addr + (int)view->img_pos
				* (test.bpp / 8) + (int)test.img_height_pos * test.line_length);
		test.color = (unsigned int)*test.dst;
		my_mlx_pixel_put(&w1->img1, test.pxl, test.draw,
			(unsigned int)test.color);
		test.draw++;
	}
	draw_ceil_floor(&test, w1, 1, &w1->img1);
}
