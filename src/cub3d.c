/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:57:41 by mafranco          #+#    #+#             */
/*   Updated: 2024/06/11 10:35:19 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

int	mouseget(t_data *w1)
{
	end(w1, "Window exit\n", 0);
	exit(0);
}

static int	checkarg(int argc, char **argv)
{
	char	*str;

	if (argc != 2)
	{
		ft_printf("Error\nThis program needs 1 path for map, \
and no more than 1 argument\n");
		return (1);
	}
	str = ft_substr(argv[1], ft_strlen(argv[1]) - 4, 4);
	if (!str)
	{
		ft_printf("Error\nFt_substr\n");
		return (1);
	}
	if (ft_strncmp(str, ".cub", 4) != 0)
	{
		free(str);
		ft_printf("Error\nThis program needs as argument a .cub map\n");
		return (1);
	}
	free(str);
	return (0);
}

int	set_values(t_data *w1)
{
	w1->size = 64;
	w1->winh = 1480;
	w1->winl = 2600;
	w1->win = mlx_new_window(w1->mlx, w1->winl, w1->winh, "./cubed");
	if (w1->win == NULL)
		return (endbefore(w1, "Error\nCreating window failed\n"));
	w1->x = (w1->startx * w1->size) + w1->size / 2;
	w1->y = (w1->starty * w1->size) + w1->size / 2;
	w1->lx = w1->x;
	w1->ly = w1->y;
	if (w1->startangle == 83)
		w1->a = PI / 2;
	else if (w1->startangle == 78)
		w1->a = 1.5 * PI;
	else if (w1->startangle == 87)
		w1->a = PI;
	else if (w1->startangle == 69)
		w1->a = 2 * PI;
	w1->dx = cos(w1->a);
	w1->dy = sin(w1->a);
	w1->rotate_speed = 0.1;
	w1->speed = (w1->size / 10);
	w1->planex = 0;
	w1->planey = 0.66;
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	w1;

	if (checkarg(argc, argv) == 1)
		return (1);
	w1.path = ft_strdup(argv[1]);
	w1.img = (void *)malloc(sizeof(t_img));
	if (!w1.img)
	{
		ft_putstr_fd("Error\nMalloc failed\n", 2);
		return (1);
	}
	if (initdata(&w1) == 1)
	{
		free(w1.img);
		return (1);
	}
	if (set_values(&w1) == 1)
		return (1);
	mlx_key_hook(w1.win, presskey, &w1);
	mlx_expose_hook(w1.win, print_view, &w1);
	mlx_hook(w1.win, 17, 1L << 17, mouseget, &w1);
	mlx_loop(w1.mlx);
	return (end(&w1, "Program end\n", 0));
}
	/*to change 2d view to 3d view, go to key_and_free.c, 
	on the bottom and change where it is told*/
	/*and put in commentaries draw_map here and mlx_loop_hook*/
	//draw_map(&w1);//	draw 2d map
	//mlx_loop_hook(w1.mlx, expose, &w1);//	draw 2d person mooving
