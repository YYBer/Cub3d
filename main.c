#include "cub3d.h"

int	init_m(t_main *m)
{
	m->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Raycaster", false);
	if (!m->mlx)
	{
		printf("Error: Could not create MLX window.\n");
		return (1);
	}
	m->img = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!m->img)
	{
		printf("Error: Could not create MLX image.\n");
		// free m->mlx
		return (1);
	}
	m->map_width = 24;
	m->map_height = 24;
	if (alloc_world_map(m))
	{
		printf("Error: Could not allocate world map.\n");
		// free m->mlx m->img
		return (1);
	}
	init_world_map(m);
	m->texture = create_texture_array();
	generate_texture(m);
	m->pos.x = 2;
	m->pos.y = 2;
	m->dir.x = 1;
	m->dir.y = 0;
	m->plane.x = 0;
	m->plane.y = 0.66;
	m->move_speed = SQRS_PER_SEC / 100; 
	m->rot_speed = RADS_PER_SEC / 100;
	m->pitch = 100;
	m->key_w_pressed = false;
	m->key_s_pressed = false;
	m->key_a_pressed = false;
	m->key_d_pressed = false;
	return (0);
}

void	my_closehook(void *param)
{
	t_main	*m;

	m = (t_main *)param;
	mlx_terminate(m->mlx);
	free_world_map(m);
	free_texture_array(m->texture);
	exit(0);
}

int	main(void)
{
	t_main	m;

	mlx_set_setting(MLX_STRETCH_IMAGE, false);
	if (init_m(&m))
		return (1);
	if ((mlx_image_to_window(m.mlx, m.img, 0, 0) < 0))
	{
		printf("Error: Could not put image to window.\n");
		return (1);
	}
	mlx_key_hook(m.mlx, &my_keyhook, &m);
	mlx_close_hook(m.mlx, &my_closehook, &m);
	mlx_loop_hook(m.mlx, ft_hook, &m);
	mlx_loop(m.mlx);
	mlx_terminate(m.mlx);
	free_world_map(&m);
	return (0);
}