/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus_flags2.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/26 16:24:10 by gbooth            #+#    #+#             */
/*   Updated: 2023/02/03 13:57:41 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

char	*pad_zeros(char *str, int num_zeros_to_pad)
{
	char	*zeros;
	char	*ret_str;
	bool	leading_minus;

	leading_minus = false;
	if (str[0] == '-')
		leading_minus = true;
	zeros = malloc((num_zeros_to_pad + 1) * sizeof(char));
	if (!zeros)
		return (ft_strdup(str));
	zeros[num_zeros_to_pad] = '\0';
	num_zeros_to_pad--;
	while (num_zeros_to_pad >= 0)
	{
		zeros[num_zeros_to_pad] = '0';
		num_zeros_to_pad--;
	}
	ret_str = ft_strjoin(zeros, str);
	if (leading_minus == true)
	{
		ret_str[0] = '-';
		ret_str[ft_strlen(zeros)] = '0';
	}
	free(zeros);
	return (ret_str);
}

char	*zero_flag__pad_left_zeros(char *str, t_pf *flags)
{
	int	num_zeros_to_pad;

	if (flags->zero__pad_left_zeros_flag == true \
		&& flags->pad_left_zeros_total_len > 0)
	{
		num_zeros_to_pad = flags->pad_left_zeros_total_len - ft_strlen(str);
		if (num_zeros_to_pad > 0)
			return (pad_zeros(str, num_zeros_to_pad));
	}
	return (ft_strdup(str));
}

char	*dot_flag__put_prec(char *str, t_pf *flags)
{
	int		num_zeros_to_pad;
	char	*str_tofree;

	if (str[0] == '-')
		flags->prec++;
	if (flags->dot__prec_flag == true && flags->prec == 0)
	{
		free(str);
		return (ft_strdup(""));
	}
	if (flags->dot__prec_flag == true && flags->prec > ft_strlen(str))
	{		
		num_zeros_to_pad = flags->prec - ft_strlen(str);
		if (num_zeros_to_pad > 0)
		{
			str_tofree = str;
			str = pad_zeros(str_tofree, num_zeros_to_pad);
			free(str_tofree);
			return (str);
		}
	}
	return (str);
}

// if(str[0] == 0) flags->pad_right_blanks_total_len--;
char	*minus_flag__pad_right_spaces(char *str, t_pf *flags)
{
	int		num_blanks_to_pad;
	char	*blanks;
	char	*ret_str;		

	if (flags->minus__pad_right_spaces_flag == true \
		&& flags->pad_right_blanks_total_len > 0)
	{
		num_blanks_to_pad = flags->pad_right_blanks_total_len - ft_strlen(str);
		if (num_blanks_to_pad > 0)
		{
			blanks = malloc((num_blanks_to_pad + 1) * sizeof(char));
			if (!blanks)
				return (ft_strdup(str));
			blanks[num_blanks_to_pad] = '\0';
			num_blanks_to_pad--;
			while (num_blanks_to_pad >= 0)
				blanks[num_blanks_to_pad--] = ' ';
			ret_str = ft_strjoin(str, blanks);
			free(blanks);
			return (ret_str);
		}
	}
	return (ft_strdup(str));
}

// if(str[0] == 0)	flags->field_width--;
char	*integer_flag__field_width(char *str, t_pf *flags)
{
	int		num_blanks_to_pad;
	char	*blanks;
	char	*ret_str;

	if (flags->integer__field_width_flag == true && \
		flags->minus__pad_right_spaces_flag == false && flags->field_width > 0)
	{
		num_blanks_to_pad = flags->field_width - ft_strlen(str);
		if (num_blanks_to_pad > 0)
		{
			blanks = malloc((num_blanks_to_pad + 1) * sizeof(char));
			if (!blanks)
				return (ft_strdup(str));
			blanks[num_blanks_to_pad] = '\0';
			num_blanks_to_pad--;
			while (num_blanks_to_pad >= 0)
				blanks[num_blanks_to_pad--] = ' ';
			ret_str = ft_strjoin(blanks, str);
			free(blanks);
			return (ret_str);
		}
	}
	ret_str = ft_strdup(str);
	return (ret_str);
}
