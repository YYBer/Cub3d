#include "cub3d.h"

void init_map(t_map *map, char *filename)
{
    *map = get_map_dims(filename);
    if (map->nrows == -1)
    {
        printf("invalid character in map\n");
        exit(EXIT_FAILURE);
    }
    printf("map dimensions: %i %i\n", map->nrows, map->ncols);
    fill_map(map, filename);
}

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
	init_map(&m->map, m->filename);
	print_map(&m->map);
	// printf("Q: are x and y coords the right way round? %i\n", m->map.data[1][3]);
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

void my_closehook(void *param)
{
	t_main	*m;

	m = (t_main *)param;
	mlx_terminate(m->mlx);
	free_map_data(&m->map);
	free_texture_array(m->texture);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_main	m;

	if(argc != 2)
	{
		printf("wrong number of args\n"); // replace with ft_printf
		return(1);
	}
	m.filename = argv[1];

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
	mlx_loop_hook(m.mlx, ft_raycast, &m);
	mlx_loop(m.mlx);
	mlx_terminate(m.mlx);
	free_map_data(&m.map);
	return (0);
}