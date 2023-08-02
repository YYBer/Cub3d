#include "cub3d.h"

void	my_keyhook(mlx_key_data_t keydata, void *param)
{
	t_main	*m;

	m = (t_main *)param;
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
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		mlx_terminate(m->mlx);
		free_world_map(m);
		exit(0);
	}
}

