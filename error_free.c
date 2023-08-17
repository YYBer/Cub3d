/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:32:45 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/17 09:41:20 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *str, t_main *m)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
	write(2, "\n", 1);
	if (m)
	{
		if (m->texture_alloc == true)
			delete_textures(m);
		if (m->map.data_alloc == true)
			free_map_data(&m->map);
	}
}

void	delete_textures(t_main *m)
{
	mlx_delete_texture(m->textures[0]);
	mlx_delete_texture(m->textures[1]);
	mlx_delete_texture(m->textures[2]);
	mlx_delete_texture(m->textures[3]);
}

void	my_closehook(void *param)
{
	t_main	*m;

	m = (t_main *)param;
	mlx_terminate(m->mlx);
	free_map_data(&m->map);
	delete_textures(m);
	exit(0);
}

void	free_map_data(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->nrows)
	{
		free(map->data_c[i]);
		free(map->data_i[i]);
		i++;
	}
	free(map->data_c);
	free(map->data_i);
}
