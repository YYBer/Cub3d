/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:41:26 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/18 16:20:42 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	keys_ws(mlx_key_data_t keydata, t_main *m)
{
	if (keydata.key == MLX_KEY_W)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			m->key_w_pressed = true;
		if (keydata.action == MLX_RELEASE)
			m->key_w_pressed = false;
	}
	if (keydata.key == MLX_KEY_S)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			m->key_s_pressed = true;
		if (keydata.action == MLX_RELEASE)
			m->key_s_pressed = false;
	}
}

void	keys_ad(mlx_key_data_t keydata, t_main *m)
{
	if (keydata.key == MLX_KEY_A)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			m->key_a_pressed = true;
		if (keydata.action == MLX_RELEASE)
			m->key_a_pressed = false;
	}
	if (keydata.key == MLX_KEY_D)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			m->key_d_pressed = true;
		if (keydata.action == MLX_RELEASE)
			m->key_d_pressed = false;
	}
}

void	keys_left_right(mlx_key_data_t keydata, t_main *m)
{
	if (keydata.key == MLX_KEY_LEFT)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			m->key_left_pressed = true;
		if (keydata.action == MLX_RELEASE)
			m->key_left_pressed = false;
	}
	if (keydata.key == MLX_KEY_RIGHT)
	{
		if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT)
			m->key_right_pressed = true;
		if (keydata.action == MLX_RELEASE)
			m->key_right_pressed = false;
	}
}

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_main	*m;

	m = (t_main *)param;
	keys_ws(keydata, param);
	keys_ad(keydata, param);
	keys_left_right(keydata, param);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(m->mlx);
		free_m(m);
		exit(0);
	}
}
