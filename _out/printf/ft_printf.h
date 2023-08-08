/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 16:51:10 by gbooth            #+#    #+#             */
/*   Updated: 2023/02/03 21:57:42 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft/libft.h"

typedef struct t_printf
{
	int		pos;
	int		len;
}	t_p;

typedef struct t_pf_flags
{
	bool	integer__field_width_flag;
	bool	zero__pad_left_zeros_flag;
	bool	minus__pad_right_spaces_flag;
	bool	dot__prec_flag;
	bool	hash_flag;
	bool	space_flag;
	bool	plus_flag;

	size_t	pad_left_zeros_total_len;
	size_t	pad_right_blanks_total_len;
	size_t	field_width;
	size_t	prec;
}	t_pf;

int		ft_printf(const char *fs, ...);
int		ft_vprintf(const char *fs, va_list ap);
void	ft_convert(const char *fs, t_p *p, va_list ap, t_pf *flags);
void	ft_convert_c(va_list ap, t_p *p, t_pf *flags);

void	ft_convert_s(va_list ap, t_p *p, t_pf *flags);
void	ft_convert_di(va_list ap, t_p *p, t_pf *flags);
void	ft_convert_p(va_list ap, t_p *p, t_pf *flags);
void	ft_convert_u(va_list ap, t_p *p, t_pf *flags);
void	ft_convert_x(const char fs, va_list ap, t_p *p, t_pf *flags);

void	init_flags(t_pf *flags);
void	ft_flags(const char *fs, t_p *p, t_pf *flags);

char	*pad_zeros(char *str, int num_zeros_to_pad);
char	*zero_flag__pad_left_zeros(char *str, t_pf *flags);
char	*dot_flag__put_prec(char *str, t_pf *flags);
char	*minus_flag__pad_right_spaces(char *str, t_pf *flags);
char	*integer_flag__field_width(char *str, t_pf *flags);

void	ft_putchar(char c);
void	ft_putstr(char *str);
char	*decimal_to_hex(unsigned long decimal, bool uppercase);
void	field_width_overrides_zero_flag_for_numeric_conversions(t_pf *flags);
int		extract_int(const char *fs, t_p *p);

char	*ft_uitoa(unsigned int n);

#endif