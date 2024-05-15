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

void	freeall(char **table, int i)
{
	while (i >= 0)
	{
		free(table[i]);
		i--;
	}	
	free(table);
}

static int	maketable(t_data *w1, int fd)
{
	char	*buf;
	char	*line;
	char	*buf2;
	int		i;

	i = 0;
	buf = get_next_line(fd);
	w1->lenght = ft_strlen(buf) - 1;
	line = NULL;
	buf2 = NULL;
	while (buf)
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
	w1->table = ft_split(line, '\n');
	free(line);
	return (i);
}

static int	checkimg(t_data *w1)
{
	t_img	*ptr;

	ptr = &w1->img;
	if (!ptr->dog || !ptr->grass || !ptr->kennel || !ptr->hotdog || !ptr->fence)
		return (1);
	return (0);
}

int	makeimg(t_data *w1)
{
	w1->img.h = 45;
	w1->img.w = 45;
	w1->img.pathdog = "./xpmfiles/dog.xpm";
	w1->img.pathgrass = "./xpmfiles/grass.xpm";
	w1->img.pathkennel = "./xpmfiles/kennel.xpm";
	w1->img.pathhotdog = "./xpmfiles/hotdog.xpm";
	w1->img.pathfence = "./xpmfiles/fence.xpm";
	w1->img.dog = mlx_xpm_file_to_image(w1->mlx,
			w1->img.pathdog, &(w1->img.h), &(w1->img.w));
	w1->img.grass = mlx_xpm_file_to_image(w1->mlx,
			w1->img.pathgrass, &(w1->img.h), &(w1->img.w));
	w1->img.kennel = mlx_xpm_file_to_image(w1->mlx,
			w1->img.pathkennel, &(w1->img.h), &(w1->img.w));
	w1->img.hotdog = mlx_xpm_file_to_image(w1->mlx,
			w1->img.pathhotdog, &(w1->img.h), &(w1->img.w));
	w1->img.fence = mlx_xpm_file_to_image(w1->mlx,
			w1->img.pathfence, &(w1->img.h), &(w1->img.w));
	return (checkimg(w1));
}

int	initdata(t_data *w1)
{
	int	fd;

	fd = open(w1->path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\nOPENING FILE FAILED");
		return (0);
	}
	w1->width = maketable(w1, fd);
	close(fd);
	if (w1->width == 0)
		return (0);
	printf("lenght == %d, width == %d\n", w1->lenght, w1->width);
	close(fd);
	w1->count = 0;
	w1->moove = 0;
	if (w1->table == NULL)
		return (endbefore(w1, "MALLOC FAILED"));
	if (checkmap(w1) == 1)
		return (1);
	//if (checkpath(w1, 1, 0, 0) == 1)
	//	return (endbefore(w1, "MAP NEEDS A VALID WAY TO WIN"));
	w1->mlx = mlx_init();
	if (w1->mlx == NULL)
		return (endbefore(w1, "MLX FAILED TO INIT"));
	return (0);
}
