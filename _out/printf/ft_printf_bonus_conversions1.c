/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus_conversions1.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:50:56 by gbooth            #+#    #+#             */
/*   Updated: 2023/02/03 21:49:49 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	ft_convert_c2(t_p *p, t_pf *flags)
{
	size_t	i;

	i = 0;
	while (i < flags->pad_right_blanks_total_len - 1)
	{
		ft_putchar(' ');
		p->len++;
		i++;
	}
}

// field width, minus_flag__pad_right_spaces
void	ft_convert_c(va_list ap, t_p *p, t_pf *flags)
{
	size_t	i;

	p->len++;
	if (flags->minus__pad_right_spaces_flag == true && \
		flags->pad_right_blanks_total_len > 0)
	{
		ft_putchar(va_arg(ap, int));
		ft_convert_c2(p, flags);
	}
	else if (flags->integer__field_width_flag == true && \
		flags->minus__pad_right_spaces_flag == false && flags->field_width > 0)
	{
		i = 0;
		while (i < flags->field_width - 1)
		{
			ft_putchar(' ');
			i++;
		}
		ft_putchar(va_arg(ap, int));
		p->len++;
	}
	else
		ft_putchar(va_arg(ap, int));
}

// DONE: dot__prec(max chars), minus_flag
void	ft_convert_s(va_list ap, t_p *p, t_pf *flags)
{
	char	*str;
	char	*str_tofree;

	str = va_arg(ap, char *);
	if (str == NULL && flags->dot__prec_flag == true && flags->prec < 6)
		str = ft_strdup("");
	else if (str == NULL)
		str = ft_strdup("(null)");
	else
		str = ft_strdup(str);
	if (flags->dot__prec_flag == true && flags->prec < ft_strlen(str))
	{
		str_tofree = str;
		str = ft_substr(str_tofree, 0, flags->prec);
		free(str_tofree);
	}
	str_tofree = str;
	str = minus_flag__pad_right_spaces(str_tofree, flags);
	free(str_tofree);
	str_tofree = str;
	str = integer_flag__field_width(str_tofree, flags);
	free(str_tofree);
	ft_putstr(str);
	p->len += ft_strlen(str);
	free(str);
}

void	ft_convert_di2(int value, t_p *p, t_pf *flags)
{
	if (value >= 0 && flags->space_flag == true)
	{
		ft_putchar(' ');
		p->len++;
	}
	if (value >= 0 && flags->plus_flag == true)
	{
		ft_putchar('+');
		p->len++;
	}
}

// DONE: zero_flag, dot__prec (min), minus_flag
void	ft_convert_di(va_list ap, t_p *p, t_pf *flags)
{
	char	*ret_str;
	char	*str_tofree;
	int		value;

	value = va_arg(ap, int);
	ft_convert_di2(value, p, flags);
	ret_str = ft_itoa(value);
	field_width_overrides_zero_flag_for_numeric_conversions(flags);
	str_tofree = ret_str;
	ret_str = zero_flag__pad_left_zeros(str_tofree, flags);
	free(str_tofree);
	ret_str = dot_flag__put_prec(ret_str, flags);
	str_tofree = ret_str;
	ret_str = minus_flag__pad_right_spaces(str_tofree, flags);
	free(str_tofree);
	str_tofree = ret_str;
	ret_str = integer_flag__field_width(str_tofree, flags);
	free(str_tofree);
	ft_putstr(ret_str);
	p->len += ft_strlen(ret_str);
	free(ret_str);
}
