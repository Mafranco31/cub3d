/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:57:31 by mafranco          #+#    #+#             */
/*   Updated: 2024/06/11 10:31:57 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

int	create_mlx_image(t_data *w1, int y)
{
	w1->img->h = y;
	w1->img->l = y;
	w1->img->n = mlx_xpm_file_to_image(w1->mlx,
			w1->img->pathn, &(w1->img->h), &(w1->img->l));
	if (!w1->img->n)
		return (err_creating_mlx(w1, 1, "Error: mlx failed to \
create North oriented wall image\n"));
	w1->img->s = mlx_xpm_file_to_image(w1->mlx,
			w1->img->paths, &(w1->img->h), &(w1->img->l));
	if (!w1->img->s)
		return (err_creating_mlx(w1, 2, "Error: mlx failed to \
create South oriented wall image\n"));
	w1->img->e = mlx_xpm_file_to_image(w1->mlx,
			w1->img->pathe, &(w1->img->h), &(w1->img->l));
	if (!w1->img->e)
		return (err_creating_mlx(w1, 3, "Error: mlx failed to \
create East oriented wall image\n"));
	w1->img->we = mlx_xpm_file_to_image(w1->mlx,
			w1->img->pathw, &(w1->img->h), &(w1->img->l));
	if (!w1->img->we)
		return (err_creating_mlx(w1, 4, "Error: mlx failed to \
create West oriented wall image\n"));
	return (0);
}

int	check_unique(char **ptr, char *buf, char *str)
{
	int	i;

	i = 0;
	while (buf[i] && !ft_isspace_char(buf[i]))
		i++;
	if (ft_isspace_char(buf[i]))
		return (err_msg_elements(buf, 1, 1));
	if (*ptr)
	{
		ft_putstr_fd("Error\nElement in double\n", 2);
		free(buf);
		free(str);
		return (1);
	}
	*ptr = buf;
	return (0);
}

int	add_element(t_data *w1, char *str, char *buf)
{
	buf = ft_strtrim(str + 2, "\t\n\v\f\r ");
	if (!buf)
	{
		ft_putstr_fd("Error\nError in : ft_strtrim\n", 2);
		free(str);
		return (1);
	}
	if (!ft_strncmp(str, "NO ", 3))
		return (check_unique(&w1->img->pathn, buf, str));
	else if (!ft_strncmp(str, "SO ", 3))
		return (check_unique(&w1->img->paths, buf, str));
	else if (!ft_strncmp(str, "EA ", 3))
		return (check_unique(&w1->img->pathe, buf, str));
	else if (!ft_strncmp(str, "WE ", 3))
		return (check_unique(&w1->img->pathw, buf, str));
	else if (!ft_strncmp(str, "F ", 2))
		return (get_color_char_to_int(&w1->img->color_bot, buf, str));
	else if (!ft_strncmp(str, "C ", 2))
		return (get_color_char_to_int(&w1->img->color_top, buf, str));
	else
	{
		free(buf);
		return (err_msg_elements(str, 1, 1));
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
			if (ft_strlen(buf) < 3)
				return (err_msg_elements(buf, 1, 1));
			if (add_element(w1, buf, NULL) == 1)
				return (1);
			count += 1;
		}
		free(buf);
		if (count < 6)
			buf = get_next_line(fd);
	}
	return (create_mlx_image(w1, w1->size));
}

int	initdata(t_data *w1)
{
	int	fd;

	fd = open(w1->path, O_RDONLY);
	if (fd == -1)
	{
		free(w1->path);
		ft_putstr_fd("Error\nError opening file\n", 2);
		return (1);
	}
	if (init_paths(w1, fd) == 1)
		return (1);
	w1->width = maketable(w1, fd);
	close(fd);
	if (w1->width == 0)
		return (err_width_zero(w1));
	if (checkmap(w1) == 1)
		return (1);
	if (w1->mlx == NULL)
		return (endbefore(w1, "Error\nMlx failed to initialise\n"));
	return (0);
}
