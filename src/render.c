/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:34:36 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/17 16:17:03 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

// in while loop:
// calculate ray position and direction
// length of ray from current position to next x or y-side
void	ft_raycast(void *param)
{
	t_main	*m;
	int		x;

	m = (t_main *)param;
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
