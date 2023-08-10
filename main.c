#include "cub3d.h"

void init_m(char **argv, t_main *m)
{
	m->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Raycaster", false);
	if (!m->mlx)
	{
		//printf("Error: Could not create MLX window.\n");
		ft_error("Error: Could not create MLX window.", m);
		exit(EXIT_FAILURE);
	}
	m->img = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!m->img)
	{
		//printf("Error: Could not create MLX image.\n");
		// free m->mlx
		ft_error("Error: Could not create MLX image.", m);
		exit(EXIT_FAILURE);
	}
	m->filename = argv[1];
	m->num_chars_read = 0;
	open_subject_file(m);
	read_subject_file(m);
    get_map_dims(m);
    // printf("map dimensions: %i %i\n", m->map.nrows, m->map.ncols);
    fill_map(m);
	close(m->fd);
	m->texture_alloc = false;
	if (ft_map_parameters_check(m))
		exit(1);
	print_map(&m->map);
	// printf("Q: are x and y coords the right way round? %i\n", m->map.data[1][3]);
	m->textures = create_textures();
	m->texture_alloc = true;
	generate_textures(m);
	m->pos.x = 2;
	m->pos.y = 2;
	// change this based on whether N S E W in map
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
}

void my_closehook(void *param)
{
	t_main	*m;

	m = (t_main *)param;
	mlx_terminate(m->mlx);
	free_map_data(&m->map);
	free_textures(m->textures);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_main	m;

	if (ft_check_map_command(argc, argv))
		exit(1);
	mlx_set_setting(MLX_STRETCH_IMAGE, false);
	init_m(argv, &m);
	if ((mlx_image_to_window(m.mlx, m.img, 0, 0) < 0))
	{
		//printf("Error: Could not put image to window.\n");
		ft_error("Error: Could not put image to window.", &m);
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(m.mlx, &my_keyhook, &m);
	mlx_close_hook(m.mlx, &my_closehook, &m);
	mlx_loop_hook(m.mlx, ft_raycast, &m);
	mlx_loop(m.mlx);
	mlx_terminate(m.mlx);
	free_map_data(&m.map);
	return(EXIT_SUCCESS);
}