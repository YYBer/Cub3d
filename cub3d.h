
#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include "MLX42.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define TEX_WIDTH 64
#define TEX_HEIGHT 64
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
}	t_map;

// comment all vars below
typedef struct s_main {
	char 			*filename;
	t_map 			map;
	mlx_t			*mlx;
	mlx_image_t		*img;
	int				***textures;
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
	double			perp_wall_dist;
	int				lineHeight;
	int				pitch;
	bool			key_w_pressed;
	bool			key_s_pressed;
	bool			key_d_pressed;
	bool			key_a_pressed;
}	t_main;

int			alloc_map(t_main *m);
void		init_map(t_map *map, char *filename);
void		free_map(t_main *m);
void		my_keyhook(mlx_key_data_t keydata, void *param);
void		ft_raycast(void *param);
void		move_player(t_main *m);
t_pt2d_d	calc_ray_dir(int x, t_pt2d_d raydr, t_pt2d_d dir, t_pt2d_d plane);
t_pt2d_d 	calc_delta_dist(t_pt2d_d delta_dist, t_pt2d_d raydr);
void		calc_step_and_side_dist(t_main *m);
int			perform_dda(t_main *m);
double		getperp_wall_dist(int side, t_pt2d_d side_dist, t_pt2d_d delta_dist);
void		draw_tex(t_main *m, int x);
void		draw_tex2(t_main *m, int x, int drawStart, int drawEnd);
void  		generate_textures(t_main *m);
int*** 		create_textures();
void		free_textures(int*** textures);
t_map		get_map_dims(char *filename);
void		fill_map(t_map *map, char *filename);
void 		print_map(t_map *map);
void		free_map_data(t_map *map);
int	ft_check_map_command(int argc, char **argv);

#endif