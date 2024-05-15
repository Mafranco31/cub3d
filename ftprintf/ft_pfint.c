/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pfint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:07:33 by mafranco          #+#    #+#             */
/*   Updated: 2023/07/25 21:11:25 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	intmin(int n)
{
	(void)n;
	if (write(1, "-2147483648", 11) != 11)
		return (-1);
	return (11);
}

int	pfputnbr(int n)
{
	int	let;

	let = 0;
	if (n == -2147483648)
		return (intmin(n));
	if (n < 0 && ++let)
	{
		if (write(1, "-", 1) != 1)
			return (-1);
		n = -n;
	}
	if (n > 9)
	{
		let += pfputnbr(n / 10);
		if (let == -1)
			return (-1);
		n = n % 10;
	}
	if (n <= 9)
	{
		if (pfputchar(('0' + n)) == -1)
			return (-1);
		let++;
	}
	return (let);
}

int	pfputhexa(unsigned int nbr, char *s)
{
	int	i;

	i = 0;
	if (!nbr)
		return (-1);
	if (nbr >= 16)
	{
		i += pfputhexa((nbr / 16), s);
		if (i == -1)
			return (-1);
		if (pfputchar(s[(nbr % 16)]) == -1)
			return (-1);
		i++;
	}
	else
	{
		if (pfputchar(s[(nbr % 16)]) == -1)
			return (-1);
		i++;
	}
	return (i);
}

int	pfputnbruns(unsigned int nbr)
{
	int	ret;

	ret = 0;
	if (nbr > 9)
	{
		ret = pfputnbruns(nbr / 10);
		if (ret == -1)
			return (-1);
		nbr = nbr % 10;
	}
	if (nbr <= 9)
	{
		if (pfputchar(('0' + nbr)) == -1)
			return (-1);
		ret++;
	}
	return (ret);
}
