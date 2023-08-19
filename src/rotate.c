/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:34:40 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/19 13:43:19 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// for all functions below...
// both camera direction and camera plane must be rotated
void	rotate_left(t_main *m)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = m->dir.x;
	m->dir.x = m->dir.x * cos(m->rot_speed) - m->dir.y * sin(m->rot_speed);
	m->dir.y = olddir_x * sin(m->rot_speed) + m->dir.y * cos(m->rot_speed);
	oldplane_x = m->plane.x;
	m->plane.x = m->plane.x * cos(m->rot_speed)
		- m->plane.y * sin(m->rot_speed);
	m->plane.y = oldplane_x * sin(m->rot_speed)
		+ m->plane.y * cos(m->rot_speed);
}

void	rotate_right(t_main *m)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = m->dir.x;
	m->dir.x = m->dir.x * cos(-m->rot_speed) - m->dir.y * sin(-m->rot_speed);
	m->dir.y = olddir_x * sin(-m->rot_speed) + m->dir.y * cos(-m->rot_speed);
	oldplane_x = m->plane.x;
	m->plane.x = m->plane.x * cos(-m->rot_speed)
		- m->plane.y * sin(-m->rot_speed);
	m->plane.y = oldplane_x * sin(-m->rot_speed)
		+ m->plane.y * cos(-m->rot_speed);
}

void	rotate_mouse(t_main *m, double mouse_delta)
{
	double	olddir_x;
	double	oldplane_x;

	olddir_x = m->dir.x;
	m->dir.x = m->dir.x * cos(mouse_delta) - m->dir.y * sin(mouse_delta);
	m->dir.y = olddir_x * sin(mouse_delta) + m->dir.y * cos(mouse_delta);
	oldplane_x = m->plane.x;
	m->plane.x = m->plane.x * cos(mouse_delta)
		- m->plane.y * sin(mouse_delta);
	m->plane.y = oldplane_x * sin(mouse_delta)
		+ m->plane.y * cos(mouse_delta);
}
