// TODO: fix ERROR: cannot parse map file(read_prefixes) - we are one char too far ahead
// DONE: Except for the map, each type of information from an element can be separated by one or more space(s). [???]

#include "cub3d.h"

void convert_map_data_c_to_i(t_main *m)
{
    int col;
    int row;


	malloc_map_i(&m->map);

	// fill map i
    row = 0;
    while(row < m->map.nrows)
    {
		col = 0;
        while(col < m->map.ncols)
        {
			char char_str[2];

            if (m->map.data_c[row][col] == 'N' || m->map.data_c[row][col] == 'S' || m->map.data_c[row][col] == 'W' || m->map.data_c[row][col] == 'E')
                m->map.data_i[row][col] = 0;
            else if (m->map.data_c[row][col] == ' ')
                m->map.data_i[row][col] = -1;
            else
			{
				char_str[0] = m->map.data_c[row][col];
				char_str[1] = '\0';
				m->map.data_i[row][col] = atoi(char_str);
			}
            col++;
        }
        row++;
    }
}

void init_window(t_main *m)
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
}

// printf("tex_paths:\nNO:%s\nSO:%s\nWE:%s\nEA:%s\n", m->tex_paths[0], m->tex_paths[1], m->tex_paths[2], m->tex_paths[3]);
// printf("map dimensions: %i %i\n", m->map.nrows, m->map.ncols);
// print_map(&m->map);
// printf("Q: are x and y coords the right way round? %i\n", m->map.data[1][3]);
void init_m(char **argv, t_main *m)
{
	read_subject_file(argv, m);
    get_map_dims(m);
    fill_map(m);
	print_map_c(&m->map);
	convert_map_data_c_to_i(m);
	print_map_i(&m->map);	
	// if (ft_map_parameters_check(m))
	// 	exit(1);
	load_textures(m);
	m->move_speed = SQRS_PER_SEC / 100; 
	m->rot_speed = RADS_PER_SEC / 100;
	m->pitch = 100;
	m->key_w_pressed = false;
	m->key_s_pressed = false;
	m->key_a_pressed = false;
	m->key_d_pressed = false;
	m->key_left_pressed = false;
	m->key_right_pressed = false;	
	init_window(m);
}

void my_closehook(void *param)
{
	t_main	*m;

	m = (t_main *)param;
	mlx_terminate(m->mlx);
	free_map_data(&m->map);
	delete_textures(m);
	exit(0);
}

void load_textures(t_main *m)
{
	m->texture_alloc = false;
    printf("0: \"%s\"\n", m->tex_paths[0]);
    printf("1: \"%s\"\n", m->tex_paths[1]);
    printf("2: \"%s\"\n", m->tex_paths[2]);
    printf("3: \"%s\"\n", m->tex_paths[3]);
    m->textures[0] = mlx_load_png(m->tex_paths[0]);
    m->textures[1] = mlx_load_png(m->tex_paths[1]);
    m->textures[2] = mlx_load_png(m->tex_paths[2]);
    m->textures[3] = mlx_load_png(m->tex_paths[3]);
}

void delete_textures(t_main *m)
{
    mlx_delete_texture(m->textures[0]);
	mlx_delete_texture(m->textures[1]);
	mlx_delete_texture(m->textures[2]);
	mlx_delete_texture(m->textures[3]);
}

int	main(int argc, char **argv)
{
	t_main	m;

	if (ft_check_map_command(argc, argv))
		exit(1);
	mlx_set_setting(MLX_STRETCH_IMAGE, false);
	init_m(argv, &m);
	if (strcmp(argv[2], "test") == 0)
		exit(EXIT_SUCCESS);
	if ((mlx_image_to_window(m.mlx, m.img, 0, 0) < 0))
	{
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