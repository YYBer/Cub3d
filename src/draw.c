/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:32:37 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/18 15:02:52 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_floor_ceiling(t_main *m, int x)
{
	int	y;

	y = 0;
	while (y < m->draw_start)
	{
		mlx_put_pixel(m->img, x, y, m->ceiling_color);
		y++;
	}
	y = m->draw_end;
	while (y < WIN_HEIGHT)
	{
		mlx_put_pixel(m->img, x, y, m->floor_color);
		y++;
	}
}

void	draw_tex3(t_main *m, int x, int tex_x)
{
	double		step;
	double		tex_pos;
	int			y;
	u_int8_t	*pixel;
	int			tex_y;

	step = 1.0 * m->textures[m->wall_direction]->height / m->line_height;
	tex_pos = (m->draw_start - m->pitch - WIN_HEIGHT / 2 + m->line_height / 2)
		* step;
	y = m->draw_start;
	while (y < m->draw_end)
	{
		tex_y = (int)tex_pos & (m->textures[m->wall_direction]->height - 1);
		tex_pos += step;
		pixel = &m->textures[m->wall_direction]->pixels[(tex_x + tex_y
				* m->textures[m->wall_direction]->width)
			* m->textures[m->wall_direction]->bytes_per_pixel];
		mlx_put_pixel(m->img, x, y,
			pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]);
		y++;
	}
}

void	draw_tex2(t_main *m, int x)
{
	double	wall_x;
	int		tex_x;

	if (m->side == 0)
		wall_x = m->pos.y + m->perp_wall_dist * m->raydr.y;
	else
		wall_x = m->pos.x + m->perp_wall_dist * m->raydr.x;
	wall_x -= floor((wall_x));
	tex_x = (int)(wall_x * m->textures[m->wall_direction]->width);
	if (m->side == 0 && m->raydr.x > 0)
		tex_x = m->textures[m->wall_direction]->width - tex_x - 1;
	if (m->side == 1 && m->raydr.y < 0)
		tex_x = m->textures[m->wall_direction]->width - tex_x - 1;
	draw_tex3(m, x, tex_x);
}

// Calculate height of line to draw on screen
// check for 'm->draw_end < 0' protects against...
// ...it going negative when outer wall reached
void	draw_tex(t_main *m, int x)
{
	m->draw_start = 0;
	m->draw_end = 0;
	m->line_height = (int)(WIN_HEIGHT / m->perp_wall_dist);
	m->draw_start = -m->line_height / 2 + WIN_HEIGHT / 2 + m->pitch;
	if (m->draw_start < 0)
		m->draw_start = 0;
	m->draw_end = m->line_height / 2 + WIN_HEIGHT / 2 + m->pitch;
	if (m->draw_end >= WIN_HEIGHT || m->draw_end < 0)
		m->draw_end = WIN_HEIGHT - 1;
	draw_floor_ceiling(m, x);
	draw_tex2(m, x);
}
