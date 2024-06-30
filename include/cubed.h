/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlitran <dlitran@student.42barcelona.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 14:56:48 by mafranco          #+#    #+#             */
/*   Updated: 2024/06/13 10:00:28 by dlitran          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include "mlx/mlx.h"
# include <stdio.h>
# include <unistd.h>
# include "../libft/libft.h"
# include "../ftprintf/ft_printf.h"
# include <fcntl.h>
# include <math.h>
# define PI 3.1415926535

typedef struct s_view
{
	int		x;
	double	val_angle;
	int		dist;
	double	angle;
	int		mapx;
	int		mapy;
	double	side_distx;
	double	side_disty;
	double	delta_distx;
	double	delta_disty;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		wall_pos;
	int		opposite;
	int		img_pos;
	void	*texture;
	double	final_angle;
	double	angle_plan;
}	t_view;

typedef struct s_test
{
	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;
	unsigned int	color;
	double			img_height_pos;
	int				draw;
	unsigned int	*dst;
	int				drawstart;
	int				drawposstart;
	int				drawend;
	int				i;
	int				pxl;
}	t_test;

typedef struct s_imgstr
{
	void	*img;
	char	*addr;
	int		bpp;
	int		line_length;
	int		endian;
}	t_imgstr;

typedef struct s_rgb
{
	int	r;
	int	g;
	int	b;
	int	i;
	int	j;
	int	k;
}	t_rgb;

typedef struct s_img
{
	char	*pathn;
	char	*paths;
	char	*pathe;
	char	*pathw;
	void	*n;
	void	*s;
	void	*e;
	void	*we;
	int		h;
	int		l;
	int		color_top;
	int		color_bot;
	int		dogx;
	int		dogy;
}		t_img;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	double	ldx;
	double	ldy;
	double	la;
	double	dx;
	double	dy;
	double	a;
	int		len_file;
	double	planex;
	double	planey;
	double	rotate_speed;
	char	startangle;
	double	x;
	int		lx;
	double	y;
	int		ly;
	int		startx;
	int		starty;
	int		lenght;
	int		width;
	int		winh;
	int		winl;
	int		size;
	int		speed;
	t_img	*img;
	t_test	img1;
	char	**table;
	char	*path;
}		t_data;

int		ft_isspace_char(char str);

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

void	draw_map(t_data *w1);

void	draw_line(t_data *w1, double dx, double dy, int color);

void	put_square(int x, int y, t_data *w1, int c);

void	draw_looking_view(t_data *w1);

int		print_view(t_data *w1);

int		print_view2(t_data *w1);

int		err_msg_elements(char *buf, int free_buf, int ret_num);

int		err_creating_mlx(t_data *w1, int nb, char *str);

int		err_width_zero(t_data *w1);

int		init_paths(t_data *w1, int fd);

int		get_color_char_to_int(int *ptr, char *str, char *str_all);

int		maketable(t_data *w1, int fd);

int		check_fd_size(int fd);

void	draw_vertical_line(t_data *w1, int dist, t_view *view);

void	modif_print_view(t_data *w1, t_view *view);

#endif
