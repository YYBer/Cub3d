#include "cub3d.h"

void	clear_image(t_main *m)
{
	unsigned int	x;
	unsigned int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			mlx_put_pixel(m->img, x, y, 0x000000FF);
			x++;
		}
		y++;
	}
}

// cast rays!
void	ft_hook(void *param)
{
	t_main	*m;
	int		x;

	m = (t_main *)param;
	move_player(m);
	clear_image(m);
	x = 0;
	while (x < WIN_WIDTH)
	{
		//calculate ray position and direction
		//length of ray from current position to next x or y-side:
		m->raydr = calc_ray_dir(x, m->raydr, m->dir, m->plane);
		m->map.x = (int)(m->pos.x);
		m->map.y = (int)(m->pos.y);
		m->delta_dist = calc_delta_dist(m->delta_dist, m->raydr);
		calc_step_and_side_dist(m);
		m->side = perform_dda(m);
		m->perp_wall_dist
			= getperp_wall_dist(m->side, m->side_dist, m->delta_dist);
		draw_ver_line(m, x);
		x++;
	}
}