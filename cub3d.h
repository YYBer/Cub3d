
#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <stdbool.h>
#include "MLX42.h"
#include "libft/libft.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define SQRS_PER_SEC 5.0
#define RADS_PER_SEC 3.0
#define NUM_TEXTURES 4

#define COLOUR_RED 0xFF0000FF
#define COLOUR_BLUE 0x00FF00FF
#define COLOUR_GREEN 0x0000FFFF
#define COLOUR_WHITE 0xFFFFFFFF
#define COLOUR_YELLOW 0XFFFF00FF

typedef struct s_point2Dd {
	double	x;
	double	y;
}	t_pt2d_d;

typedef struct s_point2Di {
	int	x;
	int	y;
}	t_pt2d_i;

typedef struct s_map {
	int	nrows;
	int	ncols;
    char **data;
	bool	data_alloc;
}	t_map;

// comment all vars below
typedef struct s_main {
	char 			*filename;
	int				fd;
	int				num_chars_read;
	char			*tex_paths[4];
	t_map 			map;
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t*	textures[4];
	bool			texture_alloc;
	t_pt2d_d		pos; // start position:	
	t_pt2d_d		dir; // initial direction vector:
	t_pt2d_d		plane; // 2d raycaster version of camera plane:
	t_pt2d_d		raydr;
	t_pt2d_d		side_dist;
	t_pt2d_d		delta_dist;
	t_pt2d_i		map_pos; // which square the player is in on the map
	t_pt2d_i		step; //what direction to step in x or y-direction (either +1 or -1)
	t_pt2d_i		tex;
	double			move_speed;
	double			rot_speed;
	int				side;
	int				wall_direction;
	double			perp_wall_dist;
	int				lineHeight;
	int				pitch;
	bool			key_w_pressed;
	bool			key_s_pressed;
	bool			key_d_pressed;
	bool			key_a_pressed;
	bool			key_left_pressed;
	bool			key_right_pressed;	
	int				ceiling_color;
	int				floor_color;
}	t_main;

int			alloc_map(t_main *m);
void 		read_subject_file(char **argv, t_main *m);
void		read_tex_filenames(t_main *m);
int 		read_color_value(t_main *m, char *onecharbuf);
void 		load_textures(t_main *m);
void		delete_textures(t_main *m);
void		free_map(t_main *m);
void		my_keyhook(mlx_key_data_t keydata, void *param);
void		ft_raycast(void *param);
void		move_player(t_main *m);
t_pt2d_d	calc_ray_dir(int x, t_pt2d_d raydr, t_pt2d_d dir, t_pt2d_d plane);
t_pt2d_d 	calc_delta_dist(t_pt2d_d delta_dist, t_pt2d_d raydr);
void		calc_step_and_side_dist(t_main *m);
void			perform_dda(t_main *m);
double		getperp_wall_dist(int side, t_pt2d_d side_dist, t_pt2d_d delta_dist);
void		draw_tex(t_main *m, int x);
void		draw_tex2(t_main *m, int x, int drawStart, int drawEnd);
void		get_map_dims(t_main *m);
void 		fill_map(t_main *m);
void 		print_map(t_map *map);
void		free_map_data(t_map *map);
void		ft_error(char *str, t_main *m);
int			ft_check_map_command(int argc, char **argv);
int			ft_map_parameters_check(t_main *m);
void 		check_map_position(int x, int y, t_main *m);
#endif