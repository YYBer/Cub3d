#include "cub3d.h"

// camera_x = x-coordinate in camera space
t_pt2d_d	calc_ray_dir(int x, t_pt2d_d raydr, t_pt2d_d dir, t_pt2d_d plane)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	raydr.x = dir.x + plane.x * camera_x;
	raydr.y = dir.y + plane.y * camera_x;
	return (raydr);
}

t_pt2d_d calc_delta_dist(t_pt2d_d delta_dist, t_pt2d_d raydr)
{
	if (raydr.x == 0)
		delta_dist.x = 1e30;
	else
		delta_dist.x = fabs(1 / raydr.x);
	if (raydr.y == 0)
		delta_dist.y = 1e30;
	else
		delta_dist.y = fabs(1 / raydr.y);
	return (delta_dist);
}

//calculate step and initial side_dist
void	calc_step_and_side_dist(t_main *m)
{
	if (m->raydr.x < 0)
	{
		m->step.x = -1;
		m->side_dist.x = (m->pos.x - m->map.x) * m->delta_dist.x;
	}
	else
	{
		m->step.x = 1;
		m->side_dist.x = (m->map.x + 1.0 - m->pos.x) * m->delta_dist.x;
	}
	if (m->raydr.y < 0)
	{
		m->step.y = -1;
		m->side_dist.y = (m->pos.y - m->map.y) * m->delta_dist.y;
	}
	else
	{
		m->step.y = 1;
		m->side_dist.y = (m->map.y + 1.0 - m->pos.y) * m->delta_dist.y;
	}
}

// hit = was there a wall hit?
// side = was a NS or a EW wall hit?
int	perform_dda(t_main *m)
{
	int	hit; 
	int	side; 

	hit = 0;
	while (hit == 0)
	{
		//jump to next map square, either in x-direction, or in y-direction
		if (m->side_dist.x < m->side_dist.y)
		{
			m->side_dist.x += m->delta_dist.x;
			m->map.x += m->step.x;
			side = 0;
		}
		else
		{
			m->side_dist.y += m->delta_dist.y;
			m->map.y += m->step.y;
			side = 1;
		}
		//Check if ray has hit a wall
		if (m->world_map[m->map.x][m->map.y] > 0)
			hit = 1;
	}
	return (side);
}

double	getperp_wall_dist(int side, t_pt2d_d side_dist, t_pt2d_d delta_dist)
{
	if (side == 0)
	  	return (side_dist.x - delta_dist.x);
	return (side_dist.y - delta_dist.y);
}
