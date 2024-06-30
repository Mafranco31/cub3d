/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_view3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:59:32 by mafranco          #+#    #+#             */
/*   Updated: 2024/06/29 10:59:33 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

static void	modif_values_print_view4(t_data *w1, t_view *view)
{
	if (view->x < w1->winl / 2)
		view->angle_plan = w1->a - PI / 2;
	else
		view->angle_plan = w1->a + PI / 2;
	if (view->angle_plan < 0)
		view->angle_plan += 2 * PI;
	if (view->angle_plan > 2 * PI)
		view->angle_plan -= 2 * PI;
	if (view->x < w1->winl / 2)
		view->final_angle = view->angle - view->angle_plan;
	else
		view->final_angle = view->angle_plan - view->angle;
	if (view->final_angle < 0)
		view->final_angle += 2 * PI;
	if (view->final_angle > 2 * PI)
		view->final_angle -= 2 * PI;
}

static void	modif_values_print_view3(t_data *w1, t_view *view)
{
	while (view->hit == 0)
	{
		if (view->side_distx < view->side_disty)
		{
			view->side_distx += view->delta_distx;
			view->mapx += view->stepx;
			view->side = 0;
		}
		else
		{
			view->side_disty += view->delta_disty;
			view->mapy += view->stepy;
			view->side = 1;
		}
		if (view->mapx >= w1->lenght || view->mapy >= w1->width
			|| view->mapx < 0 || view->mapy < 0)
		{
			view->hit = 1;
			break ;
		}
		if (w1->table[view->mapy][view->mapx] == 49)
			view->hit = 1;
	}
	modif_values_print_view4(w1, view);
}

static void	modif_values_print_view2(t_data *w1, t_view *view)
{
	view->hit = 0;
	view->dist = 0;
	view->delta_distx = fabs((w1->size) / cos(view->angle));
	if ((view->angle < PI) && (view->angle > 0))
	{
		view->stepy = 1;
		if (sin(view->angle) == 0)
			view->side_disty = 1000000000000;
		else
			view->side_disty = (w1->size - ((int)w1->y % w1->size))
				/ sin(view->angle);
	}
	else
	{
		view->stepy = -1;
		if (sin(view->angle) == 0)
			view->side_disty = 1000000000000;
		else
			view->side_disty = fabs(((((int)w1->y) % w1->size))
					/ sin(view->angle));
	}
	view->delta_disty = fabs((w1->size) / sin(view->angle));
	modif_values_print_view3(w1, view);
}

void	modif_print_view(t_data *w1, t_view *view)
{
	view->mapx = w1->x / w1->size;
	view->mapy = w1->y / w1->size;
	if (view->angle < 0)
		view->angle += 2 * PI;
	if (view->angle > 2 * PI)
		view->angle -= 2 * PI;
	if ((view->angle > 1.5 * PI) || (view->angle < (PI / 2)))
	{
		view->stepx = 1;
		if (cos(view->angle) == 0)
			view->side_distx = 1000000000000;
		else
			view->side_distx = (w1->size - ((int)w1->x % w1->size))
				/ cos(view->angle);
	}
	else
	{
		view->stepx = -1;
		if (cos(view->angle) == 0)
			view->side_distx = 1000000000000;
		else
			view->side_distx = fabs((((int)w1->x) % w1->size)
					/ cos(view->angle));
	}
	modif_values_print_view2(w1, view);
}
