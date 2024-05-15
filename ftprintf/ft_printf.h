/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafranco <mafranco@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 09:24:26 by mafranco          #+#    #+#             */
/*   Updated: 2023/07/25 21:18:23 by mafranco         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>

int		pfputunsin(unsigned int nbr, char c);

int		pfputnbruns(unsigned int nbr);

int		pfputcdi(int nb, char c);

int		debut(va_list args, char str);

int		ft_printf(const char *str, ...);

int		pfputptr(unsigned long long int ptr);

int		pfputchar(int c);

size_t	pfstrlen(const char *s);

int		pfputstr(char *s);

int		intmin(int n);

int		pfputnbr(int nbr);

int		pfputhexa(unsigned int nbr, char *s);

int		pfptrhex(unsigned long long int nb, int i);

#endif
