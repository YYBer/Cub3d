//TODO: read map from file and include in main struct
//TODO: norminette what you've got!
//TODO: leak check (currently it seems MLX42 itself leaks)

// REMOVED FPS COUNTER:
// double time = 0; //time of current frame
// double oldTime = 0; //time of previous frame
// double frameTime;
//timing for input and FPS counter
// oldTime = time;
// time = getTicks();
// frameTime = (time - oldTime) / 1000.0;
// print(1.0 / frameTime); //FPS counter
// m.move_speed = frameTime * SQRS_PER_SEC; 
// m.rot_speed = frameTime * RADS_PER_SEC;

#ifndef CUB3D_H
# define CUB3D_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480
#define SQRS_PER_SEC 5.0
#define RADS_PER_SEC 3.0

extern int wm[24][24];

typedef struct s_point2Dd {
	double	x;
	double	y;
}	t_pt2d_d;

typedef struct s_point2Di {
	int	x;
	int	y;
}	t_pt2d_i;

// comment all vars below
typedef struct s_main {
	int				map_width;
	int				map_height;
	int				**world_map;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_pt2d_d		pos; // start position:	
	t_pt2d_d		dir; // initial direction vector:
	t_pt2d_d		plane; // 2d raycaster version of camera plane:
	t_pt2d_d		raydr;
	t_pt2d_d		side_dist;
	t_pt2d_d		delta_dist;
	t_pt2d_i		map;
	t_pt2d_i		step; //what direction to step in x or y-direction (either +1 or -1)
	double			move_speed;
	double			rot_speed;
	int				side;
	double			perp_wall_dist;
	bool			key_w_pressed;
	bool			key_s_pressed;
	bool			key_d_pressed;
	bool			key_a_pressed;
}	t_main;

int			alloc_world_map(t_main *m);
void		init_world_map(t_main *m);
void		free_world_map(t_main *m);
void		my_keyhook(mlx_key_data_t keydata, void *param);
void		ft_hook(void *param);
void		move_player(t_main *m);
t_pt2d_d	calc_ray_dir(int x, t_pt2d_d raydr, t_pt2d_d dir, t_pt2d_d plane);
t_pt2d_d 	calc_delta_dist(t_pt2d_d delta_dist, t_pt2d_d raydr);
void		calc_step_and_side_dist(t_main *m);
int			perform_dda(t_main *m);
double		getperp_wall_dist(int side, t_pt2d_d side_dist, t_pt2d_d delta_dist);
void		draw_ver_line(t_main *m, int x);

#endif