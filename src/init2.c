/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:59:11 by mafranco          #+#    #+#             */
/*   Updated: 2024/06/29 10:59:12 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

int	err_msg_elements(char *buf, int free_buf, int ret_num)
{
	if (free_buf)
		free(buf);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(".cub file should contain 6 elements \
before map description :\n", 2);
	ft_putstr_fd("- NO [path_to_the_North_Oriented_Wall_Image],\n", 2);
	ft_putstr_fd("- SO [path_to_the_South_Oriented_Wall_Image],\n", 2);
	ft_putstr_fd("- EA [path_to_the_East_Oriented_Wall_Image],\n", 2);
	ft_putstr_fd("- WE [path_to_the_West_Oriented_Wall_Image],\n", 2);
	ft_putstr_fd("- F [RGB code of floor color as (255,0,0)],\n", 2);
	ft_putstr_fd("- C [RGB code of sky color as (255,0,0)]\n", 2);
	ft_putstr_fd("And no more elements !\n", 2);
	return (ret_num);
}

void	go_end_fd(int fd)
{
	char	*buf;

	buf = get_next_line(fd);
	while (buf)
	{
		free(buf);
		buf = get_next_line(fd);
	}
	close(fd);
}

int	init_paths(t_data *w1, int fd)
{
	w1->mlx = mlx_init();
	w1->img->pathn = NULL;
	w1->img->paths = NULL;
	w1->img->pathe = NULL;
	w1->img->pathw = NULL;
	w1->img->color_bot = -1;
	w1->img->color_top = -1;
	if (makeimg(w1, fd) > 0)
	{
		free(w1->path);
		free_img_str(w1);
		mlx_destroy_display(w1->mlx);
		go_end_fd(fd);
		free(w1->mlx);
		return (1);
	}
	return (0);
}

int	err_width_zero(t_data *w1)
{
	mlx_destroy_image(w1->mlx, w1->img->n);
	mlx_destroy_image(w1->mlx, w1->img->s);
	mlx_destroy_image(w1->mlx, w1->img->e);
	mlx_destroy_image(w1->mlx, w1->img->we);
	free_img_str(w1);
	mlx_destroy_display(w1->mlx);
	free(w1->path);
	free(w1->mlx);
	return (1);
}

int	err_creating_mlx(t_data *w1, int nb, char *str)
{
	if (nb > 1)
		mlx_destroy_image(w1->mlx, w1->img->n);
	if (nb > 2)
		mlx_destroy_image(w1->mlx, w1->img->s);
	if (nb > 3)
		mlx_destroy_image(w1->mlx, w1->img->e);
	if (nb > 4)
		mlx_destroy_image(w1->mlx, w1->img->we);
	ft_putstr_fd(str, 2);
	return (1);
}
