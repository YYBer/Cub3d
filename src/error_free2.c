/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 15:59:27 by yli               #+#    #+#             */
/*   Updated: 2023/08/18 17:25:43 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	ft_tex_paths(t_main *m)
{
	int	n;

	n = 0;
	while (n < NUM_TEXTURES)
	{
		if (m->tex_paths[n])
			free(m->tex_paths[n]);
		n++;
	}
}

void	free_map_c(t_map *map)
{
	int	i;

	i = 0;
	if (map->data_c)
	{
		while (i < map->nrows)
			free(map->data_c[i++]);
		free(map->data_c);
	}
}

void	free_map_i(t_map *map)
{
	int	i;

	i = 0;
	if (map->data_i != NULL)
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
		delete_textures(m);
	if (m->map.c_alloc == true)
		free_map_c(&m->map);
	if (m->map.i_alloc == true)
		free_map_i(&m->map);
	if (m->tex_paths_alloc == true)
		ft_tex_paths(m);
}
