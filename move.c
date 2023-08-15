#include "cub3d.h"

//move forward if no wall in front of you
void	move_forwards(t_main *m)
{
	if (m->map.data_i[(int)(m->pos.x + m->dir.x * m->move_speed)][(int)(m->pos.y)] == false)
		m->pos.x += m->dir.x * m->move_speed;
	if (m->map.data_i[(int)(m->pos.x)][(int)(m->pos.y + m->dir.y * m->move_speed)] == false)
		m->pos.y += m->dir.y * m->move_speed;
}

//move backwards if no wall behind you
void	move_backwards(t_main *m)
{
	if (m->map.data_i[(int)(m->pos.x - m->dir.x * m->move_speed)][(int)(m->pos.y)] == false)
		m->pos.x -= m->dir.x * m->move_speed;
	if (m->map.data_i[(int)(m->pos.x)][(int)(m->pos.y - m->dir.y * m->move_speed)] == false)
		m->pos.y -= m->dir.y * m->move_speed;
}

// move left if no wall on the left side
void move_left(t_main *m)
{
    double side_x = m->dir.y; // Perpendicular vector to the direction
    double side_y = -m->dir.x;

    if (m->map.data_i[(int)(m->pos.x + side_x * m->move_speed)][(int)(m->pos.y)] == false)
	{
        m->pos.x += side_x * m->move_speed;
		if (m->pos.x <= 1.05)
			m->pos.x = 1.05;
	}
    if (m->map.data_i[(int)(m->pos.x)][(int)(m->pos.y + side_y * m->move_speed)] == false)
	{
        m->pos.y += side_y * m->move_speed;
	}
	// printf("pos:%f %f\n", m->pos.x, m->pos.y);
}

// move right if no wall on the right side
void move_right(t_main *m)
{
    double side_x = -m->dir.y; // Perpendicular vector to the direction
    double side_y = m->dir.x;

    if (m->map.data_i[(int)(m->pos.x + side_x * m->move_speed)][(int)(m->pos.y)] == false)
	{
    	m->pos.x += side_x * m->move_speed;
		if (m->pos.x >= m->map.nrows -1.05)
			m->pos.x = m->map.nrows -1.05;
	}    
	
    if (m->map.data_i[(int)(m->pos.x)][(int)(m->pos.y + side_y * m->move_speed)] == false)
	{
        m->pos.y += side_y * m->move_speed;
		// if (m->pos.y < 2)
		// 	m->pos.y = 2;
		// if (m->pos.y >= m->map.nrows -1)
		// 	m->pos.y = m->map.nrows;
	}
	// printf("pos:%f %f\n", m->pos.x, m->pos.y);
}

//both camera direction and camera plane must be rotated
void	rotate_left(t_main *m)
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

//both camera direction and camera plane must be rotated
void	rotate_right(t_main *m)
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
