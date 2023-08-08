/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 15:51:44 by gbooth            #+#    #+#             */
/*   Updated: 2023/05/09 11:22:25 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_printf(const char *fs, ...)
{
	int		len;
	va_list	ap;

	va_start(ap, fs);
	len = ft_vprintf(fs, ap);
	va_end(ap);
	return (len);
}

void	ft_vprintf2(const char *fs, va_list ap, t_p *p, t_pf *flags)
{
	while (fs[p->pos])
	{
		if (fs[p->pos] == '%')
		{
			p->pos++;
			ft_flags(fs, p, flags);
			ft_convert(fs, p, ap, flags);
		}
		else
		{
			ft_putchar(fs[p->pos++]);
			p->len++;
		}
	}
}

int	ft_vprintf(const char *fs, va_list ap)
{
	t_p		*p;
	t_pf	*flags;
	int		len;

	if (fs == NULL)
		return (-1);
	p = malloc(sizeof(t_p));
	flags = malloc(sizeof(t_pf));
	p->pos = 0;
	p->len = 0;
	ft_vprintf2(fs, ap, p, flags);
	len = p->len;
	free(flags);
	free(p);
	return (len);
}

void	field_width_overrides_zero_flag_for_numeric_conversions(t_pf *flags)
{
	if (flags->zero__pad_left_zeros_flag == true && \
		flags->dot__prec_flag == true)
	{
		flags->zero__pad_left_zeros_flag = false;
		flags->integer__field_width_flag = true;
		flags->field_width = flags->pad_left_zeros_total_len;
	}
}

void	ft_convert(const char *fs, t_p *p, va_list ap, t_pf *flags)
{
	if (fs[p->pos] == 'c')
		ft_convert_c(ap, p, flags);
	if (fs[p->pos] == 's')
		ft_convert_s(ap, p, flags);
	if (fs[p->pos] == 'd' || fs[p->pos] == 'i')
		ft_convert_di(ap, p, flags);
	if (fs[p->pos] == 'p')
		ft_convert_p(ap, p, flags);
	if (fs[p->pos] == 'u')
		ft_convert_u(ap, p, flags);
	if (fs[p->pos] == 'x' || fs[p->pos] == 'X')
		ft_convert_x(fs[p->pos], ap, p, flags);
	if (fs[p->pos] == 'c' || fs[p->pos] == 's' || \
		fs[p->pos] == 'd' || fs[p->pos] == 'i' || \
		fs[p->pos] == 'p' || fs[p->pos] == 'u' || \
		fs[p->pos] == 'x' || fs[p->pos] == 'X')
		p->pos++;
	else if (fs[p->pos] == '%')
	{
		ft_putstr("%");
		p->pos++;
		p->len++;
	}
	else
		p->len = -1;
}
