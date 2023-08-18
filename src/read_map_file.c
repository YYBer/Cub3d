/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:34:23 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/18 11:41:51 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	read_subject_file(char **argv, t_main *m)
{
	m->filename = argv[1];
	m->total_chars_read = 0; 
	m->fd = open(m->filename, O_RDONLY);
	if (m->fd == -1)
		ft_error(ERR_FILE, m);
	init_fileflags(m);
	read_prefixes(m);
	read_prefixes(m);
	read_prefixes(m);
	read_prefixes(m);
	read_prefixes(m);
	read_prefixes(m);
	while (m->char_read == '\n')
		read_char(m);
	get_map_dims(m);
	fill_map(m);
	get_player_position(m);
	convert_map_data_c_to_i(m);
	load_textures(m);
}

void	set_player_pos(t_main *m, int row, int col, bool *found)
{
	if (m->map_char == 'N' || m->map_char == 'S'
		|| m->map_char == 'W' || m->map_char == 'E')
	{
		if (*found == true)
			ft_error(ERR_DUP_PLAYPOS, m);
		m->pos.x = row + 0.5;
		m->pos.y = col + 0.5;
		*found = true;
	}
}

void	set_player_dir_plane_we(t_main *m)
{
	if (m->map_char == 'W')
	{
		m->dir.x = 0;
		m->dir.y = -1;
		m->plane.x = 0.66;
		m->plane.y = 0;
	}
	if (m->map_char == 'E')
	{
		m->dir.x = 0;
		m->dir.y = 1;
		m->plane.x = -0.66;
		m->plane.y = 0;
	}
}

void	set_player_dir_plane(t_main *m)
{
	if (m->map_char == 'N')
	{
		m->dir.x = -1;
		m->dir.y = 0;
		m->plane.x = 0;
		m->plane.y = -0.66;
	}
	if (m->map_char == 'S')
	{
		m->dir.x = 1;
		m->dir.y = 0;
		m->plane.x = 0;
		m->plane.y = 0.66;
	}
	set_player_dir_plane_we(m);
}

// + 0.5 sets pos to middle of square
void	get_player_position(t_main *m)
{
	int		row;
	int		col;
	bool	found;

	found = false;
	row = 0;
	while (row < m->map.nrows)
	{
		col = 0;
		while (col < m->map.ncols)
		{
			m->map_char = m->map.data_c[row][col];
			set_player_pos(m, row, col, &found);
			set_player_dir_plane(m);
			col++;
		}
		row++;
	}
	if (found == false)
		ft_error(ERR_NO_PLAYPOS, m);
}
