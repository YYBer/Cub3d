/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:32:28 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/19 14:42:00 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// camera_x = x-coordinate in camera space
t_pt2d_d	calc_ray_dir(int x, t_pt2d_d raydr, t_pt2d_d dir, t_pt2d_d plane)
{
	double	camera_x;

	camera_x = 2 * x / (double)WIN_WIDTH - 1;
	camera_x = -camera_x;
	raydr.x = dir.x + plane.x * camera_x;
	raydr.y = dir.y + plane.y * camera_x;
	return (raydr);
}

t_pt2d_d	calc_delta_dist(t_pt2d_d delta_dist, t_pt2d_d raydr)
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
		m->side_dist.x = (m->pos.x - m->map_pos.x) * m->delta_dist.x;
	}
	else
	{
		m->step.x = 1;
		m->side_dist.x = (m->map_pos.x + 1.0 - m->pos.x) * m->delta_dist.x;
	}
	if (m->raydr.y < 0)
	{
		m->step.y = -1;
		m->side_dist.y = (m->pos.y - m->map_pos.y) * m->delta_dist.y;
	}
	else
	{
		m->step.y = 1;
		m->side_dist.y = (m->map_pos.y + 1.0 - m->pos.y) * m->delta_dist.y;
	}
}

void	handle_wall_hit(t_main *m, int side)
{
	m->side = side;
	if (side == 0)
	{
		if (m->step.x < 0)
			m->wall_direction = TEXTURE_NO;
		else
			m->wall_direction = TEXTURE_SO;
	}
	else
	{
		if (m->step.y < 0)
			m->wall_direction = TEXTURE_WE;
		else
			m->wall_direction = TEXTURE_EA;
	}
}

// hit = was there a wall hit?
// side = was a NS or a EW wall hit?
// m->side; // Variable to store the wall side (0 for NS, 1 for EW)
// m->wall_direction;
// Variable to store the wall direction (0 for N, 1 for S, 2 for E, 3 for W)
// 2 = West Wall
// 3 = East Wall
// 0 = North Wall
// 1 = South Wall
void	perform_dda(t_main *m)
{
	int	hit;
	int	side;

	hit = 0;
	while (hit == 0)
	{
		if (m->side_dist.x < m->side_dist.y)
		{
			m->side_dist.x += m->delta_dist.x;
			m->map_pos.x += m->step.x;
			side = 0;
		}
		else
		{
			m->side_dist.y += m->delta_dist.y;
			m->map_pos.y += m->step.y;
			side = 1;
		}
		if (m->map.data_i[m->map_pos.x][m->map_pos.y] > 0)
		{
			hit = 1;
			handle_wall_hit(m, side);
		}
	}
}
