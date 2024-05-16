/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.barcelona.>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:56:48 by mafranco          #+#    #+#             */
/*   Updated: 2023/09/18 20:33:24 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "mlx.h"
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../ftprintf/ft_printf.h"
# include <fcntl.h>
# include <math.h>

typedef struct s_img
{
	char	*pathN;
	char	*pathS;
	char	*pathE;
	char	*pathW;
	char	*pathTop;
	char	*pathBot;
	void	*N;
	void	*S;
	void	*E;
	void	*W;
	int		h;
	int		w;
	int		dogx;
	int		dogy;
}		t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		lenght;
	int		width;
	t_img	*img;
	int		count;
	char	**table;
	int		moove;
	char	*path;
}		t_data;

int		ft_isspace(char *str);

int		initdata(t_data *w1);

int		initmap(t_data *w1, int k);

int		presskey(int kcode, t_data *w1);

int		end(t_data *w1, char *str, int i);

int		checkmap(t_data *w1);

void	freeall(char **table, int i);

char	**create1tab(t_data *w1);

int		checkpath(t_data *w1, int y, int x, int i);

int		makeimg(t_data *w1, int fd);

int		endbefore(t_data *w1, char *str);

int		expose(t_data *w1);

void	free_img_str(t_data *w1);

#endif