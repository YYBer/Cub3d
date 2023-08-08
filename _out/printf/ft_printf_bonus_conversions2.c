/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus_conversions2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:50:56 by gbooth            #+#    #+#             */
/*   Updated: 2023/02/03 13:57:40 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

// DONE: minus_flag
void	ft_convert_p(va_list ap, t_p *p, t_pf *flags)
{
	unsigned long	decimal;
	char			*ret_str;
	char			*str_tofree;

	decimal = va_arg(ap, unsigned long);
	if (decimal == 0)
		ret_str = ft_strdup("(nil)");
	else
	{
		ret_str = decimal_to_hex(decimal, 0);
		str_tofree = ret_str;
		ret_str = ft_strjoin("0x", str_tofree);
		free(str_tofree);
		str_tofree = ret_str;
		ret_str = minus_flag__pad_right_spaces(str_tofree, flags);
		free(str_tofree);
		str_tofree = ret_str;
		ret_str = integer_flag__field_width(str_tofree, flags);
		free(str_tofree);
	}
	ft_putstr(ret_str);
	p->len += ft_strlen(ret_str);
	free(ret_str);
}

// DONE: zero_flag, dot__prec (min), minus_flag
void	ft_convert_u(va_list ap, t_p *p, t_pf *flags)
{
	char	*ret_str;
	char	*str_tofree;

	field_width_overrides_zero_flag_for_numeric_conversions(flags);
	ret_str = ft_uitoa(va_arg(ap, unsigned int));
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

void	ft_hf(unsigned int decimal, bool is_upper, char **ret_str, t_pf *flags)
{
	char	*str_tofree;

	if (decimal == 0)
		*ret_str = ft_strdup("0");
	else
		*ret_str = decimal_to_hex(decimal, is_upper);
	if (decimal != 0 && flags->hash_flag == true && is_upper == true)
	{
		str_tofree = *ret_str;
		*ret_str = ft_strjoin("0X", str_tofree);
		free(str_tofree);
	}
	if (decimal != 0 && flags->hash_flag == true && is_upper == false)
	{
		str_tofree = *ret_str;
		*ret_str = ft_strjoin("0x", str_tofree);
		free(str_tofree);
	}
}

// TODO: zero_flag, dot__prec (min), minus_flag
void	ft_convert_x(const char fs, va_list ap, t_p *p, t_pf *flags)
{
	unsigned int	decimal;
	char			*ret_str;
	char			*str_tofree;
	bool			is_upper;

	if (fs == 'x')
		is_upper = false;
	if (fs == 'X')
		is_upper = true;
	decimal = va_arg(ap, unsigned int);
	ft_hf(decimal, is_upper, &ret_str, flags);
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
