/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:33:57 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/18 10:47:52 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

//move forward if no wall in front of you
void	move_forwards(t_main *m)
{
	if (m->map.data_i[(int)(m->pos.x + m->dir.x
			* m->move_speed)][(int)(m->pos.y)] == false)
		m->pos.x += m->dir.x * m->move_speed;
	if (m->map.data_i[(int)(m->pos.x)][(int)(m->pos.y + m->dir.y
			* m->move_speed)] == false)
		m->pos.y += m->dir.y * m->move_speed;
}

//move backwards if no wall behind you
void	move_backwards(t_main *m)
{
	if (m->map.data_i[(int)(m->pos.x - m->dir.x
			* m->move_speed)][(int)(m->pos.y)] == false)
		m->pos.x -= m->dir.x * m->move_speed;
	if (m->map.data_i[(int)(m->pos.x)][(int)(m->pos.y - m->dir.y
			* m->move_speed)] == false)
		m->pos.y -= m->dir.y * m->move_speed;
}

// move left if no wall on the left side
void	move_left(t_main *m)
{
	double	side_x;
	double	side_y;

	side_x = -m->dir.y;
	side_y = m->dir.x;
	if (m->map.data_i[(int)(m->pos.x + side_x
			* m->move_speed)][(int)(m->pos.y)] == false)
	{
		m->pos.x += side_x * m->move_speed;
	}
	if (m->map.data_i[(int)(m->pos.x)][(int)(m->pos.y + side_y
			* m->move_speed)] == false)
	{
		m->pos.y += side_y * m->move_speed;
	}
}

// move right if no wall on the right side
void	move_right(t_main *m)
{
	double	side_x;
	double	side_y;

	side_x = m->dir.y;
	side_y = -m->dir.x;
	if (m->map.data_i[(int)(m->pos.x + side_x
			* m->move_speed)][(int)(m->pos.y)] == false)
	{
		m->pos.x += side_x * m->move_speed;
	}
	if (m->map.data_i[(int)(m->pos.x)][(int)(m->pos.y + side_y
		* m->move_speed)] == false)
	{
		m->pos.y += side_y * m->move_speed;
	}
}

// if (mouse_moved)
// 	rotate_mouse(m);
void	move_player(t_main *m)
{
	if (m->key_w_pressed)
		move_forwards(m);
	if (m->key_s_pressed)
		move_backwards(m);
	if (m->key_a_pressed)
		move_left(m);
	if (m->key_d_pressed)
		move_right(m);
	if (m->key_left_pressed)
		rotate_left(m);
	if (m->key_right_pressed)
		rotate_right(m);
}
