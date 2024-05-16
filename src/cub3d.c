/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:57:41 by mafranco          #+#    #+#             */
/*   Updated: 2023/11/22 15:10:34 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

int	ft_isspace(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (!(str[i] >= 9 && str[i] <= 13) || str[i] != 32)
			return (0);
		i++;
	}
	return (1);
}

int	mouseget(t_data *w1)
{
	end(w1, "WINDOW EXIT", 0);
	exit(0);
}

static int	checkarg(int argc, char **argv)
{
	char	*str;

	if (argc != 2)
	{
		ft_printf("Error\nTHIS PROGRAM NEEDS 1 PATH FOR MAP,");
		ft_printf(" AND NO MORE THAM 1 ARGUMENT");
		return (1);
	}
	str = ft_substr(argv[1], ft_strlen(argv[1]) - 4, 4);
	if (!str)
	{
		ft_printf("error ft_substr\n");
		return (1);
	}
	if (ft_strncmp(str, ".cub", 4) != 0)
	{
		free(str);
		ft_printf("Error\nthis program needs as argument a .cub map\n");
		return (1);
	}
	free(str);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	w1;

	ft_printf("Program start\n");
	if (checkarg(argc, argv) == 1)
		return (1);
	ft_printf("Arg checked\n");
	w1.path = ft_strdup(argv[1]);
	w1.img = (void*)malloc(sizeof(t_img));
	if (!w1.img)
	{
		ft_putstr_fd("Error: malloc\n", 2);
		return (1);
	}
	if (initdata(&w1) == 1)
	{
		free(w1.img);
		return (1);
	}
	ft_printf("Data initialized\n");
	w1.win = mlx_new_window(w1.mlx, w1.lenght * 45, w1.width * 45, "./so_long");
	if (w1.win == NULL)
		return (endbefore(&w1, "CREATING WINDOW FAILED"));
	ft_printf("Window created\n");
	/*if (makeimg(&w1) == 1)
		return (end(&w1, "CREATING IMAGES FAILED", 1));*/
	ft_printf("Images created\n");

	mlx_key_hook(w1.win, presskey, &w1);
	//mlx_expose_hook(w1.win, expose, &w1);
	//mlx_hook(w1.win, 17, 1L << 17, mouseget, &w1);
	//mlx_loop(w1.mlx);
	return (end(&w1, "Program end\n", 0));
}
