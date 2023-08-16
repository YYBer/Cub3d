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
                m->map.data_i[row][col] = 0; // convert to 0 for now to avoid segfaults! (in the end better if -1)
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

void print_tex_paths(t_main *m)
{
    printf("texture path 0: \"%s\"\n", m->tex_paths[0]);
    printf("texture path 1: \"%s\"\n", m->tex_paths[1]);
    printf("texture path 2: \"%s\"\n", m->tex_paths[2]);
    printf("texture path 3: \"%s\"\n", m->tex_paths[3]);	
}

void print_rgba(int value)
{
    // if (value < 0 || value > 0xFFFFFFFF) {
    //     printf("Input value must be between 0 and 4294967295 (0xFFFFFFFF)\n");
    //     return;
    // }

    int red = (value >> 24) & 0xFF;
    int green = (value >> 16) & 0xFF;
    int blue = (value >> 8) & 0xFF;
    int alpha = value & 0xFF;

    printf("0x%02X%02X%02X%02X", red, green, blue, alpha);
}

void print_floor_ceiling_colors(t_main *m)
{
	printf("floor color:		");
	print_rgba(m->floor_color);
	printf("\n");
	printf("ceiling color:	");	
	print_rgba(m->ceiling_color);
	printf("\n");
}

void print_cub_file_summary(t_main *m)
{
	printf("--Printing .cub file summary:\n");
	print_tex_paths(m);
	print_floor_ceiling_colors(m);
	print_map_c(&m->map);
	print_map_i(&m->map);
}

// printf("tex_paths:\nNO:%s\nSO:%s\nWE:%s\nEA:%s\n", m->tex_paths[0], m->tex_paths[1], m->tex_paths[2], m->tex_paths[3]);
// printf("map dimensions: %i %i\n", m->map.nrows, m->map.ncols);
// print_map(&m->map);
// printf("Q: are x and y coords the right way round? %i\n", m->map.data[1][3]);
void init_m(char **argv, t_main *m)
{
	read_subject_file(argv, m);
	// if (ft_map_parameters_check(m))
	// 	exit(1);
	print_cub_file_summary(m);
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
	int i;
	int fd;

	m->texture_alloc = false;
	i = 0;
	while(i < NUM_TEXTURES)
	{
		fd = open(m->tex_paths[i], O_RDONLY);
		if (fd == -1)
		{
			printf("%s%s%s\"%s\"\n", ERR_MSG, ERR_FILE, ERR_FILE_PATH, m->tex_paths[i]);
			exit(EXIT_FAILURE);
		}
		close(fd);
		m->textures[i] = mlx_load_png(m->tex_paths[i]);
		i++;
	}
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
	if (ft_surround_check(&m))
		exit(1);
	if (argc == 3 && strcmp(argv[2], "test") == 0)
		exit(EXIT_SUCCESS);
	//printf("-----print map-------\n");
	//printf("check map: %d \n", ft_surround_check(&m));
	if ((mlx_image_to_window(m.mlx, m.img, 0, 0) < 0))
	{
		ft_error("Error: Could not put image to window.", &m);
		exit(EXIT_FAILURE);
	}
	mlx_key_hook(m.mlx, &my_keyhook, &m);
	// mlx_mouse_hook(m.mlx, &my_mousehook, &m);
	mlx_close_hook(m.mlx, &my_closehook, &m);
	mlx_loop_hook(m.mlx, ft_raycast, &m);
	mlx_loop(m.mlx);
	mlx_terminate(m.mlx);
	free_map_data(&m.map);
	return(EXIT_SUCCESS);
}