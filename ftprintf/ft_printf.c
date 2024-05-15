/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/27 13:08:30 by mafranco          #+#    #+#             */
/*   Updated: 2023/07/25 21:11:17 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	pfputunsin(unsigned int nbr, char c)
{
	if (nbr == 0)
		return (pfputchar(48));
	if (c == 'u')
		return (pfputnbruns(nbr));
	else if (c == 'x')
		return (pfputhexa(nbr, "0123456789abcdef"));
	else
		return (pfputhexa(nbr, "0123456789ABCDEF"));
}

int	pfputcdi(int nb, char c)
{
	if (c == 'c')
		return (pfputchar(nb));
	else if (c == 'd')
		return (pfputnbr(nb));
	else
		return (pfputnbr(nb));
}

int	debut(va_list args, char str)
{
	if (str == '%')
		return (pfputchar('%'));
	else if (str == 's')
		return (pfputstr(va_arg(args, char *)));
	else if (str == 'd' || str == 'i' || str == 'c')
		return (pfputcdi(va_arg(args, int), str));
	else if (str == 'u' || str == 'x' || str == 'X')
		return (pfputunsin(va_arg(args, unsigned int), str));
	else if (str == 'p')
		return (pfputptr(va_arg(args, unsigned long long int)));
	else
		return (-1);
}

int	start(va_list list, const char *str)
{
	int	i;
	int	count;
	int	check;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			check = debut(list, str[i + 1]);
			if (check == -1)
				return (-1);
			count += check;
			i++;
		}
		else
		{
			if (pfputchar(str[i]) != 1)
				return (-1);
			count++;
		}
		i++;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	va_list	list;
	int		count;

	count = 0;
	va_start(list, str);
	count = start(list, str);
	va_end(list);
	return (count);
}
