/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_free1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:32:45 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/18 17:21:58 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_error(char *str, t_main *m)
{
	write(2, "Error\n", 6);
	write(2, str, (int)ft_strlen(str));
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
	free_m(m);
	exit(EXIT_FAILURE);
}
