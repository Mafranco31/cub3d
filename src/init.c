/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:57:31 by mafranco          #+#    #+#             */
/*   Updated: 2023/11/22 15:20:53 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

static int	maketable(t_data *w1, int fd)
{
	char	*buf;
	char	*line;
	char	*buf2;
	int		i;

	i = 0;

	buf = get_next_line(fd);
	if (!buf)
	{
		w1->table = NULL;
		return (1);
	}
	while (buf && !ft_strchr(buf, 49))
	{
		free(buf);
		buf = get_next_line(fd);
	}
	ft_printf("Test");
	w1->lenght = ft_strlen(buf) - 1;
	line = NULL;
	buf2 = NULL;
	while (buf && ft_strchr(buf, 49))
	{
		i++;
		buf2 = ft_strdup(line);
		free(line);
		line = ft_strjoin(buf2, buf);
		free(buf);
		free(buf2);
		if (line == NULL)
			return (0);
		buf = get_next_line(fd);
	}
	if (buf)
		free(buf);
	w1->table = ft_split(line, '\n');
	free(line);
	return (i);
}

int	err_creating_mlx(t_data *w1, int nb, char *str)
{
	if (nb > 1)
		mlx_destroy_image(w1->mlx, w1->img->N);
	if (nb > 2)
		mlx_destroy_image(w1->mlx, w1->img->S);
	if (nb > 3)
		mlx_destroy_image(w1->mlx, w1->img->E);	
	ft_putstr_fd(str, 2);
	return (1);
}


int	create_mlx_image(t_data *w1)
{
	int	y = 45;

	w1->img->h = y;
	w1->img->w = y;

	w1->img->N = mlx_xpm_file_to_image(w1->mlx,
			w1->img->pathN, &(w1->img->h), &(w1->img->w));
	if (!w1->img->N)
		return (err_creating_mlx(w1, 1, "Error: mlx failed to create North oriented wall image\n"));

	w1->img->S = mlx_xpm_file_to_image(w1->mlx,
			w1->img->pathS, &(w1->img->h), &(w1->img->w));
	if (!w1->img->S)
		return (err_creating_mlx(w1, 2, "Error: mlx failed to create South oriented wall image\n"));

	w1->img->E = mlx_xpm_file_to_image(w1->mlx,
			w1->img->pathE, &(w1->img->h), &(w1->img->w));
	if (!w1->img->E)
		return (err_creating_mlx(w1, 3, "Error: mlx failed to create East oriented wall image\n"));

	w1->img->W = mlx_xpm_file_to_image(w1->mlx,
			w1->img->pathW, &(w1->img->h), &(w1->img->w));
	if (!w1->img->W)
		return (err_creating_mlx(w1, 4, "Error: mlx failed to create West oriented wall image\n"));
	return (0);
}

int	add_element(t_data *w1, char *str)
{
	char	*buf;

	if (ft_strlen(str) < 3)
	{
		ft_putstr_fd(".cub file should contain 6 elements before map description :\n", 2);
		ft_putstr_fd("- NO [path_to_the_North_Oriented_Wall_Image],\n", 2);
		ft_putstr_fd("- SO [path_to_the_South_Oriented_Wall_Image],\n", 2);
		ft_putstr_fd("- EA [path_to_the_East_Oriented_Wall_Image],\n", 2);
		ft_putstr_fd("- WE [path_to_the_West_Oriented_Wall_Image],\n", 2);
		ft_putstr_fd("- F [RGB code of floor color as (255,0,0)],\n", 2);
		ft_putstr_fd("- C [RGB code of sky color as (255,0,0)]\n\n", 2);
		ft_putstr_fd("And no more elements !", 2);
		return (1);
	}
	buf = ft_strtrim(str + 2, "\t\n\v\f\r ");
	if (!buf)
	{
		ft_putstr_fd("Error: ft_strtrim\n", 2);
		return (1);
	}
	if (!ft_strncmp(str, "NO ", 3))
		w1->img->pathN = buf;
	else if (!ft_strncmp(str, "SO ", 3))
		w1->img->pathS = buf;
	else if (!ft_strncmp(str, "EA ", 3))
		w1->img->pathE = buf;
	else if (!ft_strncmp(str, "WE ", 3))
		w1->img->pathW = buf;
	else if (!ft_strncmp(str, "F ", 2))
		w1->img->pathBot = buf;
	else if (!ft_strncmp(str, "C ", 2))
		w1->img->pathTop = buf;
	else
	{
		ft_putstr_fd(".cub file should contain 6 elements before map description :\n", 2);
		ft_putstr_fd("- NO [path_to_the_North_Oriented_Wall_Image],\n", 2);
		ft_putstr_fd("- SO [path_to_the_South_Oriented_Wall_Image],\n", 2);
		ft_putstr_fd("- EA [path_to_the_East_Oriented_Wall_Image],\n", 2);
		ft_putstr_fd("- WE [path_to_the_West_Oriented_Wall_Image],\n", 2);
		ft_putstr_fd("- F [RGB code of floor color as (255,0,0)],\n", 2);
		ft_putstr_fd("- C [RGB code of sky color as (255,0,0)]\n\n", 2);
		ft_putstr_fd("And no more elements !\n", 2);
		free(buf);
		return (1);
	}
	return (0);
}

int	makeimg(t_data *w1, int fd)
{
	int		count;
	char	*buf;

	count = 0;
	buf = get_next_line(fd);
	while (buf && count < 6)
	{
		if (ft_strlen(buf) > 1 && !ft_isspace(buf))
		{
			if (add_element(w1, buf) == 1)
			{
				free(buf);
				return (1);
			}
			count += 1;
		}
		free(buf);
		if (count < 6)
			buf = get_next_line(fd);
	}
	return (create_mlx_image(w1));
}

int	initdata(t_data *w1)
{
	int	fd;

	fd = open(w1->path, O_RDONLY);
	if (fd == -1)
	{
		free(w1->path);
		ft_putstr_fd("Error: open argument\n", 2);
		return (0);
	}
	w1->mlx = mlx_init();
	
	if (makeimg(w1, fd) == 1)
	{
		free(w1->path);
		free_img_str(w1);
		//free(w1->img);
		return (1);
	}
	//write(1, "tess", 4);
	w1->width = maketable(w1, fd);
	close(fd);
	if (w1->width == 0)
	{
		free(w1->path);
		//free(w1->img);
		free_img_str(w1);
		ft_putstr_fd("Error: Map is empty\n", 2);
		return (1);
	}
	//printf("lenght == %d, width == %d\n", w1->lenght, w1->width);
	close(fd);
	w1->count = 0;
	w1->moove = 0;
	if (w1->table == NULL)
		return (endbefore(w1, "Error: malloc failed\n"));
	if (checkmap(w1) == 1)
		return (1);
	if (w1->mlx == NULL)
		return (endbefore(w1, "Error: mlx failed to initialise\n"));
	return (0);
}