/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:34:36 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/19 14:20:09 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	set_rotation_with_mouse(t_main *m)
{
	int		mouse_x;
	int		mouse_y;
	double	mouse_delta;

	mouse_delta = 0;
	mlx_get_mouse_pos(m->mlx, &mouse_x, &mouse_y);
	mouse_delta = -((mouse_x - m->prev_mouse_x) * 0.01);
	rotate_mouse(m, mouse_delta);
	m->prev_mouse_x = mouse_x;
}

// in while loop:
// calculate ray position and direction
// length of ray from current position to next x or y-side
void	ft_raycast(void *param)
{
	t_main	*m;
	int		x;

	m = (t_main *)param;
	set_rotation_with_mouse(m);
	move_player(m);
	clear_image(m);
	x = 0;
	while (x < WIN_WIDTH)
	{
		m->raydr = calc_ray_dir(x, m->raydr, m->dir, m->plane);
		m->map_pos.x = (int)(m->pos.x);
		m->map_pos.y = (int)(m->pos.y);
		m->delta_dist = calc_delta_dist(m->delta_dist, m->raydr);
		calc_step_and_side_dist(m);
		perform_dda(m);
		if (m->side == 0)
			m->perp_wall_dist = m->side_dist.x - m->delta_dist.x;
		else
			m->perp_wall_dist = m->side_dist.y - m->delta_dist.y;
		draw_tex(m, x);
		x++;
	}
	draw_minimap(m);
}
