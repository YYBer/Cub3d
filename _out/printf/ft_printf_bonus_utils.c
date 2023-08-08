/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus_utils.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:50:55 by gbooth            #+#    #+#             */
/*   Updated: 2023/02/01 15:03:14 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_putstr(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

int	count_hex(char **str, unsigned long quotient, bool is_upper, int *a_off)
{
	int			i;
	int			temp;

	if (is_upper == true)
		*a_off = 55;
	else
		*a_off = 87;
	i = 0;
	while (quotient != 0)
	{
		temp = quotient % 16;
		if (temp < 10)
			temp = temp + 48;
		else
			temp = temp + *a_off;
		i++;
		quotient = quotient / 16;
	}
	*str = malloc((i + 1) * sizeof(char));
	return (i);
}

char	*decimal_to_hex(unsigned long quotient, bool is_upper)
{
	char	*str;
	int		a_off;
	int		i;
	int		temp;

	if (quotient == ULONG_MAX)
		return (ft_strdup("ffffffffffffffff"));
	if (quotient == (unsigned long)LONG_MIN)
		return (ft_strdup("8000000000000000"));
	i = count_hex(&str, quotient, is_upper, &a_off);
	str[i--] = '\0';
	while (quotient != 0)
	{
		temp = quotient % 16;
		if (temp < 10)
			temp = temp + 48;
		else
			temp = temp + a_off;
		str[i--] = temp;
		quotient = quotient / 16;
	}
	return (str);
}

// extract subsequent integer digits (if any exist)
int	extract_int(const char *fs, t_p *p)
{
	int		start;
	int		len;
	char	*str;
	int		str_as_int;

	start = p->pos;
	len = 0;
	while (ft_isdigit(fs[p->pos]) || fs[p->pos] == '-' || \
		fs[p->pos] == '+')
	{
		len++;
		p->pos++;
	}
	str = ft_substr(fs, start, len);
	if (str[0] == '\0')
	{
		free(str);
		return (0);
	}
	str_as_int = ft_atoi(str);
	free(str);
	return (str_as_int);
}
