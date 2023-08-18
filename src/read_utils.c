/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:34:32 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/18 11:49:54 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_char(t_main *m)
{
	char	onechar[1];
	int		num_chars_read;

	num_chars_read = read(m->fd, &onechar, 1);
	if (num_chars_read < 1)
		ft_error(ERR_READ, m);
	m->total_chars_read += num_chars_read;
	m->char_read = onechar[0];
}

bool	match_char(t_main *m, char char_to_match)
{
	if (m->char_read == char_to_match)
	{
		return (true);
	}
	return (false);
}

void	init_fileflags(t_main *m)
{
	m->fileflags.no = false;
	m->fileflags.so = false;
	m->fileflags.we = false;
	m->fileflags.ea = false;
	m->fileflags.f = false;
	m->fileflags.c = false;
}

bool	*choose_fileflag(t_main *m, char *path)
{
	if (ft_strcmp(path, "NO") == 0)
		return (&m->fileflags.no);
	if (ft_strcmp(path, "SO") == 0)
		return (&m->fileflags.so);
	if (ft_strcmp(path, "WE") == 0)
		return (&m->fileflags.we);
	if (ft_strcmp(path, "EA") == 0)
		return (&m->fileflags.ea);
	if (ft_strcmp(path, "F") == 0)
		return (&m->fileflags.f);
	if (ft_strcmp(path, "C") == 0)
		return (&m->fileflags.c);
	return (NULL);
}

void	read_prefixes(t_main *m)
{
	read_char(m);
	while (m->char_read == '\n')
		read_char(m);
	if (read_tex_prefix(m, "NO") == true)
		return ;
	if (read_tex_prefix(m, "SO") == true)
		return ;
	if (read_tex_prefix(m, "WE") == true)
		return ;
	if (read_tex_prefix(m, "EA") == true)
		return ;
	if (read_color_prefix(m, "F") == true)
		return ;
	if (read_color_prefix(m, "C") == true)
		return ;
	ft_error(ERR_PREFIXES, m);
}
