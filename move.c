#include "cub3d.h"

//move forward if no wall in front of you
void	move_forwards(t_main *m)
{
	if (m->world_map[(int)(m->pos.x + m->dir.x
			* m->move_speed)][(int)(m->pos.y)] == false) m->pos.x += m->dir.x
			* m->move_speed;
	if (m->world_map[(int)(m->pos.x)][(int)(m->pos.y + m->dir.y
			* m->move_speed)] == false) m->pos.y += m->dir.y
			* m->move_speed;
}

//move backwards if no wall behind you
void	move_backwards(t_main *m)
{
	if (m->world_map[(int)(m->pos.x - m->dir.x
			* m->move_speed)][(int)(m->pos.y)] == false) m->pos.x -= m->dir.x
			* m->move_speed;
	if (m->world_map[(int)(m->pos.x)][(int)(m->pos.y - m->dir.y
			* m->move_speed)] == false) m->pos.y -= m->dir.y
			* m->move_speed;
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
		rotate_left(m);
	if (m->key_d_pressed)
		rotate_right(m);
}
