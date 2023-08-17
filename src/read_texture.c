/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:34:26 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/17 16:16:52 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	*read_wall_tex_path(t_main *m)
{
	char	path_str[PATH_MAX];
	int		i;

	i = 0;
	while (1)
	{
		if (m->char_read == '\n')
			break ;
		path_str[i] = m->char_read;
		i++;
		read_char(m);
	}
	path_str[i] = '\0';
	return (ft_strdup(path_str));
}

int	choose_tex_path_index(char *path)
{
	if (ft_strcmp(path, "NO") == 0)
		return (0);
	if (ft_strcmp(path, "SO") == 0)
		return (1);
	if (ft_strcmp(path, "WE") == 0)
		return (2);
	if (ft_strcmp(path, "EA") == 0)
		return (3);
	return (-1);
}

bool	read_tex_prefix(t_main *m, char *path)
{
	bool	*chosen_fileflag;
	int		tex_path_index;

	if (match_char(m, path[0]) == true)
	{
		read_char(m);
		if (match_char(m, path[1]) == true)
		{
			read_char(m);
			while (m->char_read == ' ')
				read_char(m);
			chosen_fileflag = choose_fileflag(m, path);
			if (*chosen_fileflag == true)
				ft_error("Invalid file format", m);
			tex_path_index = choose_tex_path_index(path);
			m->tex_paths[tex_path_index] = read_wall_tex_path(m);
			m->tex_paths_alloc = true;
			*chosen_fileflag = true;
			return (true);
		}
		else
			ft_error("Invalid file format", m);
	}
	return (false);
}
