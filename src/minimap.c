/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:33:49 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/18 16:48:09 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_minimap_window(t_main *m)
{
	int	dx_start;
	int	dy_start;
	int	dx_end;
	int	dy_end;
	int	exp_width;

	exp_width = MINIMAP_WIDTH * MINIMAP_BORDER_SCALE;
	dx_start = MINIMAP_OFFSET - exp_width;
	dx_end = MINIMAP_OFFSET + MINIMAP_WIDTH + exp_width;
	while (dx_start < dx_end)
	{
		dy_start = MINIMAP_OFFSET - exp_width;
		dy_end = MINIMAP_OFFSET + ((MINIMAP_WIDTH / m->map.ncols)
				* m->map.nrows) + exp_width;
		while (dy_start < dy_end)
		{
			mlx_put_pixel(m->img, dx_start, dy_start, MINIMAP_BGND_COL);
			dy_start++;
		}
		dx_start++;
	}
}

void	draw_minimap_square(t_main *m, int x, int y, uint32_t color)
{
	int	dx_start;
	int	dy_start;
	int	dx_end;
	int	dy_end;
	int	sqxy;

	sqxy = MINIMAP_WIDTH / m->map.ncols;
	dx_start = MINIMAP_OFFSET + (x * sqxy);
	dx_end = MINIMAP_OFFSET + (((x + 1) * sqxy) - 1);
	while (dx_start < dx_end)
	{
		dy_start = MINIMAP_OFFSET + (y * sqxy);
		dy_end = MINIMAP_OFFSET + (((y + 1) * sqxy) - 1);
		while (dy_start < dy_end)
		{
			mlx_put_pixel(m->img, dx_start, dy_start, color);
			dy_start++;
		}
		dx_start++;
	}
}

void	draw_line(t_main *m, int cx, int cy)
{
	int	i;
	int	px;
	int	py;
	int	sqxy;

	sqxy = MINIMAP_WIDTH / m->map.ncols;
	i = 0;
	while (i <= sqxy / 2)
	{
		px = cx + i * cos((-M_PI / 2.0) + atan2(m->dir.y, m->dir.x));
		py = cy - i * sin((-M_PI / 2.0) + atan2(m->dir.y, m->dir.x));
		mlx_put_pixel(m->img, px, py, MINIMAP_PLAYDIR_COL);
		i++;
	}
}

void	draw_player_direction_line(t_main *m, int x, int y)
{
	int		sqxy;
	int		line_center_x;
	int		line_center_y;

	sqxy = MINIMAP_WIDTH / m->map.ncols;
	line_center_x = MINIMAP_OFFSET + (x * sqxy) + sqxy / 2;
	line_center_y = MINIMAP_OFFSET + (y * sqxy) + sqxy / 2;
	draw_line(m, line_center_x, line_center_y);
}

// draw walls not walls
void	draw_minimap(t_main *m)
{
	int			x;
	int			y;
	uint32_t	color;
	int			elem;

	draw_minimap_window(m);
	x = 0;
	while (x < m->map.ncols)
	{
		y = 0;
		while (y < m->map.nrows)
		{
			elem = m->map.data_i[y][x];
			if (elem == 0)
				color = MINIMAP_EMPTY_COL;
			else if (elem == 1)
				color = MINIMAP_WALL_COL;
			draw_minimap_square(m, x, y, color);
			y++;
		}
		x++;
	}
	draw_minimap_square(m, m->pos.y, m->pos.x, MINIMAP_PLAYPOS_COL);
	draw_player_direction_line(m, m->pos.y, m->pos.x);
}
