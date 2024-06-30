/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   char_to_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:58:55 by mafranco          #+#    #+#             */
/*   Updated: 2024/06/29 10:58:58 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

static int	check_no_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == 44 || ft_isspace_char(str[i]) || ft_isdigit(str[i])))
			return (1);
		i++;
	}
	return (0);
}

static int	get_clr2(int num, int *ptr)
{
	*ptr = num;
	return (0);
}

static int	get_clr(int *i, char *str)
{
	int		j;
	int		num;
	char	*buf;

	j = *i;
	while (str[*i] && str[*i] != 44)
		*i += 1;
	buf = ft_substr(str, j, *i - j);
	if (!buf)
		return (-1);
	num = ft_atoi(buf);
	free(buf);
	*i += 1;
	return (num);
}

int	get_clr_err(char *str_all)
{
	free(str_all);
	ft_putstr_fd("Error\nRGB Code must be as follow:\n\
(r),(g),(b) with 0 <= r, g, b <= 255\n", 2);
	return (1);
}

int	get_color_char_to_int(int *ptr, char *str, char *str_all)
{
	int	i;
	int	r;
	int	g;
	int	b;

	if (ft_isspace(str) || check_no_char(str))
	{
		free(str_all);
		return (err_msg_elements(str, 1, 1));
	}
	if (*ptr != -1)
	{
		ft_putstr_fd("Error\nElement in double\n", 2);
		free(str);
		free(str_all);
		return (1);
	}
	i = 0;
	r = get_clr(&i, str);
	g = get_clr(&i, str);
	b = get_clr(&i, str);
	free(str);
	if (r > 255 || g > 255 || b > 255)
		return (get_clr_err(str_all));
	return (get_clr2((r << 16) | (g << 8) | b, ptr));
}
