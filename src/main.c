/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:41:51 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/17 20:55:56 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	init_window(t_main *m)
{
	m->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Raycaster", false);
	if (!m->mlx)
		ft_error("Error: Could not create MLX window.", m);
	m->img = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!m->img)
		ft_error("Error: Could not create MLX image.", m);
}

// add 'print_cub_file_summary(m);' below read_subject_file to diagnose issues!
void	init_m(char **argv, t_main *m)
{
	read_subject_file(argv, m);
	m->move_speed = SQRS_PER_SEC / 100; 
	m->rot_speed = RADS_PER_SEC / 100;
	m->pitch = 100;
	m->key_w_pressed = false;
	m->key_s_pressed = false;
	m->key_a_pressed = false;
	m->key_d_pressed = false;
	m->key_left_pressed = false;
	m->key_right_pressed = false;
	m->tex_paths_alloc = false;
	init_window(m);
}

void	load_textures(t_main *m)
{
	int	i;
	int	fd;

	i = 0;
	m->texture_alloc = false;
	while (i < NUM_TEXTURES)
	{
		fd = open(m->tex_paths[i], O_RDONLY);
		if (fd == -1)
			ft_error("File not found", m);
		close(fd);
		m->textures[i] = mlx_load_png(m->tex_paths[i]);
		i++;
	}
	m->texture_alloc = true;
}

int	ft_strcmp(char *str1, char *str2)
{
	int	ret;

	ret = ft_strncmp(str1, str2, ft_strlen(str1));
	return (ret);
}

// mlx_mouse_hook(m.mlx, &my_mousehook, &m);
int	main(int argc, char **argv)
{
	t_main	m;

	if (ft_check_map_command(argc, argv))
		ft_error("Incorrect map format", NULL);
	mlx_set_setting(MLX_STRETCH_IMAGE, false);
	init_m(argv, &m);
	if (ft_surround_check(&m))
		ft_error("Map is not completely surrouned by walls!", &m);
	if (argc == 3 && ft_strcmp(argv[2], "test") == 0)
		exit(EXIT_SUCCESS);
	if ((mlx_image_to_window(m.mlx, m.img, 0, 0) < 0))
		ft_error("Error: Could not put image to window.", &m);
	mlx_key_hook(m.mlx, &my_keyhook, &m);
	mlx_close_hook(m.mlx, &my_closehook, &m);
	mlx_loop_hook(m.mlx, ft_raycast, &m);
	mlx_loop(m.mlx);
	//write(1, "hello\n",5);
	mlx_terminate(m.mlx);
	//free_map_data(&m.map);
	free_m(&m);
	return (EXIT_SUCCESS);
}
