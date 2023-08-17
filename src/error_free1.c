/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:32:45 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/17 16:16:00 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	ft_error(char *str, t_main *m)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
	write(2, "\n", 1);
	if (m)
		free_m(m);
	exit(EXIT_FAILURE);
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