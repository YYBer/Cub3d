/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:59:27 by yli               #+#    #+#             */
/*   Updated: 2023/08/18 11:18:52 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_tex_paths(t_main *m)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (m->tex_paths[i])
		i++;
	while (n < i)
		free(m->tex_paths[n++]);
	free(m->tex_paths);
}

void	free_map_data(t_map *map)
{
	int	i;

	i = 0;
	if (map->data_c)
	{
		while (i < map->nrows)
			free(map->data_c[i++]);
		free(map->data_c);
	}
	i = 0;
	if (map->data_i)
	{
		while (i < map->nrows)
			free(map->data_i[i++]);
		free(map->data_i);
	}
}

void	free_m(t_main *m)
{
	if ((m->fd != -1))
		close(m->fd);
	if (m->texture_alloc == true)
	{
		delete_textures(m);
		m->texture_alloc = false;
	}
	if (m->map.data_alloc == true)
		free_map_data(&m->map);
	if (m->tex_paths_alloc == true)
		ft_tex_paths(m);
}