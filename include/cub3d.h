/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:47:07 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/19 14:41:30 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>
# include <stdbool.h>
# include "../MLX42/include/MLX42/MLX42.h"
# include "../libft/libft.h"

# define WIN_WIDTH 1200
# define WIN_HEIGHT 800
# define MINIMAP_WIDTH 250
# define MINIMAP_OFFSET 40
# define MINIMAP_BORDER_SCALE 0.05

# define SQRS_PER_SEC 5.0
# define RADS_PER_SEC 3.0
# define NUM_TEXTURES 4

# define COLOUR_RED 0xFF0000FF
# define COLOUR_BLUE 0x00FF00FF
# define COLOUR_GREEN 0x0000FFFF
# define COLOUR_WHITE 0xFFFFFFFF
# define COLOUR_YELLOW 0xFFFF00FF
# define MINIMAP_BGND_COL 0xAAAAAAFF
# define MINIMAP_WALL_COL 0x8B4513FF
# define MINIMAP_EMPTY_COL 0xADD8E6FF
# define MINIMAP_PLAYPOS_COL 0x22DD22FF
# define MINIMAP_PLAYDIR_COL 0xFFDD22FF

# define TEXTURE_NO 0
# define TEXTURE_SO 1
# define TEXTURE_WE 2
# define TEXTURE_EA 3

# define ERR_MSG "Error\n"
# define ERR_ARGS "Wrong number of arguments to program\n"
# define ERR_FILETYPE "Wrong file extension (should be .cub)\n"
# define ERR_FILE "File not found\n"
# define ERR_TEX_PATH "Invalid file format: Invalid texture file path\n"
# define ERR_READ "Could not read from file or unexpectedly reached end\n"
# define ERR_MLX_WIN "Could not create MLX window\n"
# define ERR_MLX_IMG "Could not create MLX image\n"
# define ERR_MLX_IMGWIN "Could not put image to window\n"
# define ERR_MAP_WALLS "Map is not completely surrouned by walls\n"
# define ERR_MEM_ROW "Memory allocation error for row\n"
# define ERR_MEM_ROWPTR "Memory allocation error for row pointers\n"
# define ERR_COL_VAL "Invalid file format: Invalid color value\n"
# define ERR_DUPL_TEX "Invalid file format: Duplicate texture path in file\n"
# define ERR_DUPL_COL "Invalid file format: Duplicate color path in file\n"
# define ERR_PREFIXES "Invalid file format: Prefix not NO, SO, WE, EA, F or C\n"
# define ERR_INVALID_MAP_CHAR "Invalid file format: Invalid character in map\n"
# define ERR_NO_PLAYPOS "Invalid file format: No player position\n"
# define ERR_DUP_PLAYPOS "Invalid file format: Duplicate player position\n"

typedef struct s_point2Dd {
	double	x;
	double	y;
}	t_pt2d_d;

typedef struct s_point2Di {
	int	x;
	int	y;
}	t_pt2d_i;

typedef struct s_map {
	int		nrows;
	int		ncols;
	char	**data_c;
	int		**data_i;
	bool	c_alloc;
	bool	i_alloc;
}	t_map;

typedef struct s_fileflags {
	bool	no;
	bool	so;
	bool	we;
	bool	ea;
	bool	f;
	bool	c;
}	t_fileflags;

// pos; 		// player start position
// dir; 		// initial direction vector (line from player position to )
// plane; 		// 2d raycaster version of camera plane
// raydr;		// the direction in which the ray will be cast
// side_dist;	// distance ray has to travel from its start pos to next x/y sqr
// delta_dist;	// distance between one x/y square to next x/y square
// map_pos; 	// which square the player is in on the map
// step; 		// what direction to step in x or y-direction (either +1 or -1)
typedef struct s_main {
	char			*filename;
	int				fd;
	char			char_read;
	char			map_char;
	int				total_chars_read;
	t_fileflags		fileflags;
	char			*tex_paths[4];
	bool			tex_paths_alloc;
	t_map			map;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*textures[4];
	bool			texture_alloc;
	t_pt2d_d		pos;
	t_pt2d_d		dir;
	t_pt2d_d		plane;
	t_pt2d_d		raydr;
	t_pt2d_d		side_dist;
	t_pt2d_d		delta_dist;
	t_pt2d_i		map_pos;
	t_pt2d_i		step;
	t_pt2d_i		tex;
	int				draw_start;
	int				draw_end;
	double			move_speed;
	double			rot_speed;
	int				side;
	int				wall_direction;
	double			perp_wall_dist;
	int				line_height;
	int				pitch;
	bool			key_w_pressed;
	bool			key_s_pressed;
	bool			key_d_pressed;
	bool			key_a_pressed;
	bool			key_left_pressed;
	bool			key_right_pressed;	
	uint32_t		ceiling_color;
	uint32_t		floor_color;
	int				prev_mouse_x;
}	t_main;

int			alloc_map(t_main *m);
void		read_subject_file(char **argv, t_main *m);
void		read_tex_filenames(t_main *m);
void		load_textures(t_main *m);
void		delete_textures(t_main *m);
void		free_map(t_main *m);
void		my_keyhook(mlx_key_data_t keydata, void *param);
void		my_mousehook(void *param);
void		ft_raycast(void *param);
void		move_player(t_main *m);
void		rotate_left(t_main *m);
void		rotate_right(t_main *m);
void		rotate_mouse(t_main *m, double mouse_delta);
t_pt2d_d	calc_ray_dir(int x, t_pt2d_d raydr, t_pt2d_d dir, t_pt2d_d plane);
t_pt2d_d	calc_delta_dist(t_pt2d_d delta_dist, t_pt2d_d raydr);
void		calc_step_and_side_dist(t_main *m);
void		perform_dda(t_main *m);
void		draw_tex(t_main *m, int x);
void		draw_tex2(t_main *m, int x);
void		get_map_dims(t_main *m);
void		fill_map(t_main *m);
void		print_map_c(t_map *map);
void		print_map_i(t_map *map);
void		free_map_data(t_map *map);
void		ft_error(char *str, t_main *m);
void		ft_check_map_command(int argc, char **argv);
void		get_player_position(t_main *m);
int			ft_surround_check(t_main *m);

void		init_fileflags(t_main *m);
void		read_prefixes(t_main *m);
void		read_char(t_main *m);
bool		match_char(t_main *m, char char_to_match);
bool		*choose_fileflag(t_main *m, char *path);
bool		read_tex_prefix(t_main *m, char *path);
bool		read_color_prefix(t_main *m, char *path);

void		malloc_map_i(t_main *m);
void		convert_map_data_c_to_i(t_main *m);
void		draw_minimap(t_main *m);

void		print_cub_file_summary(t_main *m);

void		my_closehook(void *param);
void		free_m(t_main *m);
int			ft_strcmp(char *str1, char *str2);

#endif