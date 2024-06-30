/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 10:59:38 by mafranco          #+#    #+#             */
/*   Updated: 2024/06/29 10:59:39 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cubed.h"

int	ft_isspace_char(char str)
{
	return ((str >= 9 && str <= 13) || str == 32);
}

int	ft_isspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] >= 9 && str[i] <= 13) || str[i] != 32)
			return (0);
		i++;
	}
	return (1);
}
