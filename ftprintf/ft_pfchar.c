/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfchar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:07:10 by mafranco          #+#    #+#             */
/*   Updated: 2023/07/25 19:08:30 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pfputchar(int c)
{
	if (write(1, &c, 1) != 1)
		return (-1);
	return (1);
}

size_t	pfstrlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	pfputstr(char *s)
{
	int	i;

	if (!s)
		return (pfputstr("(null)"));
	i = 0;
	while (s[i])
	{
		if (pfputchar(s[i]) == -1)
			return (-1);
		i++;
	}
	return (i);
}
