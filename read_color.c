/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:34:06 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/17 12:45:56 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	read_color_value(t_main *m)
{
	char	color_str[PATH_MAX];
	int		i;

	i = 0;
	while (m->char_read >= '0' && m->char_read <= '9')
	{
		color_str[i++] = m->char_read;
		read_char(m);
	}
	if (i == 0)
	{
		printf("%s%s%s", ERR_MSG, ERR_FORMAT, ERR_COL_VAL);
		close(m->fd);
		exit(EXIT_FAILURE);
	}
	color_str[i] = '\0';
	return (ft_atoi(color_str));
}

uint32_t	read_color_path(t_main *m)
{
	int	red;
	int	green;
	int	blue;

	red = read_color_value(m);
	read_char(m);
	match_char(m, ',');
	while (m->char_read == ' ')
		read_char(m);
	green = read_color_value(m);
	read_char(m);
	match_char(m, ',');
	while (m->char_read == ' ')
		read_char(m);
	blue = read_color_value(m);
	if (red < 0 || red > 255 || green < 0
		|| green > 255 || blue < 0 || blue > 255)
	{
		printf("%s%s%s", ERR_MSG, ERR_FORMAT, ERR_COL_VAL);
		close(m->fd);
		exit(EXIT_FAILURE);
	}
	return ((red << 24) | (green << 16) | (blue << 8) | 0xFF);
}

bool	read_color_prefix(t_main *m, char *path)
{
	bool	*chosen_fileflag;

	if (match_char(m, path[0]) == true)
	{
		read_char(m);
		while (m->char_read == ' ')
			read_char(m);
		chosen_fileflag = choose_fileflag(m, path);
		if (*chosen_fileflag == true)
		{
			printf("%s%s%s", ERR_MSG, ERR_FORMAT, ERR_DUPL);
			close(m->fd);
			exit(EXIT_FAILURE);
		}
		if (ft_strcmp(path, "F") == 0)
			m->floor_color = read_color_path(m);
		if (ft_strcmp(path, "C") == 0)
			m->ceiling_color = read_color_path(m);
		*chosen_fileflag = true;
		return (true);
	}
	return (false);
}
