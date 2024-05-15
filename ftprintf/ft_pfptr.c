/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfptr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:07:59 by mafranco          #+#    #+#             */
/*   Updated: 2023/07/25 19:44:28 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pfptrhex(unsigned long long int nb, int i)
{
	char	*str;

	str = "0123456789abcdef";
	if (nb >= 16)
	{
		i += pfptrhex((nb / 16), i);
		if (i == -1)
			return (-1);
		if (pfputchar(str[nb % 16]) == -1)
			return (-1);
		i++;
	}
	else
	{
		if (pfputchar(str[nb % 16]) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	pfputptr(unsigned long long int ptr)
{
	int	i;
	int	j;

	if (ptr == 0)
		return (pfputstr("0x0"));
	if (!ptr)
		return (pfputstr("(null)"));
	i = pfputstr("0x");
	if (i == -1)
		return (-1);
	j = pfptrhex(ptr, 0);
	if (j == -1)
		return (-1);
	return (i + j);
}
