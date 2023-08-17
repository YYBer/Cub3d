/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:34:40 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/17 16:17:07 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//both camera direction and camera plane must be rotated
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

//both camera direction and camera plane must be rotated
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
