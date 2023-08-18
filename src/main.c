/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:41:51 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/18 12:07:18 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_window(t_main *m)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, false);
	m->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "Raycaster", false);
	if (!m->mlx)
		ft_error(ERR_MLX_WIN, m);
	m->img = mlx_new_image(m->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!m->img)
		ft_error(ERR_MLX_IMG, m);
	if ((mlx_image_to_window(m->mlx, m->img, 0, 0) < 0))
		ft_error(ERR_MLX_IMGWIN, m);	
}

// add 'print_cub_file_summary(m);' below read_subject_file to diagnose issues!
void	init_m(int argc, char **argv, t_main *m)
{
	read_subject_file(argv, m);
	if (argc == 3 && ft_strcmp(argv[2], "test") == 0)
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
	m->tex_paths_alloc = false;
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
			ft_error(ERR_TEX_PATH, m);
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

	ft_check_map_command(argc, argv);
	init_m(argc, argv, &m);
	if (ft_surround_check(&m))
		ft_error(ERR_MAP_WALLS, &m);
	if (argc == 3 && ft_strcmp(argv[2], "test") == 0)
		exit(EXIT_SUCCESS);
	init_window(&m);
	mlx_key_hook(m.mlx, &my_keyhook, &m);
	mlx_close_hook(m.mlx, &my_closehook, &m);
	mlx_loop_hook(m.mlx, ft_raycast, &m);
	mlx_loop(m.mlx);
	mlx_terminate(m.mlx);
	//free_map_data(&m.map);
	free_m(&m);
	return (EXIT_SUCCESS);
}
