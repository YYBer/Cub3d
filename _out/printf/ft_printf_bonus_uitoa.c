/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus_uitoa.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/20 21:34:00 by gbooth            #+#    #+#             */
/*   Updated: 2023/02/01 15:03:14 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

unsigned int	get_length_of_str_as_uint(unsigned int n)
{
	unsigned int	l;

	l = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char	*uitoa_generate_chars(char *a, unsigned int n, unsigned int l)
{
	a[l] = '\0';
	l--;
	while (l > 0)
	{
		a[l] = 48 + (n % 10);
		n = n / 10;
		l--;
	}
	a[l] = 48 + (n % 10);
	return (a);
}

char	*ft_uitoa(unsigned int n)
{
	unsigned int		l;
	char				*a;

	l = get_length_of_str_as_uint(n);
	a = malloc(sizeof(char) * l + 1);
	if (!a)
		return (NULL);
	a = uitoa_generate_chars(a, n, l);
	return (a);
}
