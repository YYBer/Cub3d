/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus_flags1.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:23:12 by gbooth            #+#    #+#             */
/*   Updated: 2023/02/03 21:50:55 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

void	init_flags(t_pf *flags)
{	
	flags->integer__field_width_flag = false;
	flags->zero__pad_left_zeros_flag = false;
	flags->minus__pad_right_spaces_flag = false;
	flags->dot__prec_flag = false;
	flags->hash_flag = false;
	flags->space_flag = false;
	flags->plus_flag = false;
}

void	ft_flags__zero(const char *fs, t_p *p, t_pf *flags)
{
	int	extracted;

	if (fs[p->pos] == '0')
	{
		p->pos++;
		extracted = extract_int(fs, p);
		if (extracted >= 0)
		{
			flags->zero__pad_left_zeros_flag = true;
			flags->pad_left_zeros_total_len = extracted;
		}
		else
		{
			flags->minus__pad_right_spaces_flag = true;
			flags->pad_right_blanks_total_len = extracted * -1;
		}
	}
}

void	ft_flags__int_minus_dot(const char *fs, t_p *p, t_pf *flags)
{
	if (fs[p->pos] >= '1' && fs[p->pos] <= '9')
	{
		flags->integer__field_width_flag = true;
		flags->field_width = extract_int(fs, p);
	}
	if (fs[p->pos] == '-')
	{
		flags->minus__pad_right_spaces_flag = true;
		p->pos++;
		flags->pad_right_blanks_total_len = extract_int(fs, p);
	}
	if (fs[p->pos] == '.')
	{
		flags->dot__prec_flag = true;
		p->pos++;
		flags->prec = extract_int(fs, p);
	}
}

void	ft_flags__hash_space_plus(const char *fs, t_p *p, t_pf *flags)
{
	if (fs[p->pos] == '#')
	{
		flags->hash_flag = true;
		p->pos++;
	}
	if (fs[p->pos] == ' ')
	{
		flags->space_flag = true;
		p->pos++;
	}
	if (fs[p->pos] == '+')
	{
		flags->plus_flag = true;
		p->pos++;
	}
}

void	ft_flags(const char *fs, t_p *p, t_pf *flags)
{
	init_flags(flags);
	ft_flags__hash_space_plus(fs, p, flags);
	ft_flags__zero(fs, p, flags);
	ft_flags__int_minus_dot(fs, p, flags);
}
