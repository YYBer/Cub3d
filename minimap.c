#include "cub3d.h"

void draw_minimap_window(t_main *m)
{
	int dxStart;
	int dyStart;
	int dxEnd;
	int dyEnd;
	int expWidth;

	expWidth = MINIMAP_WIDTH * MINIMAP_BORDER_SCALE;	
	dxStart = MINIMAP_OFFSET - expWidth;
	dxEnd = MINIMAP_OFFSET + MINIMAP_WIDTH + expWidth;
	while(dxStart < dxEnd)
	{
		dyStart = MINIMAP_OFFSET - expWidth;
		dyEnd = MINIMAP_OFFSET + ((MINIMAP_WIDTH / m->map.ncols) * m->map.nrows) + expWidth;
		while(dyStart < dyEnd)
		{
			mlx_put_pixel(m->img, dxStart, dyStart, MINIMAP_BGND_COL);
			dyStart++;
		}
		dxStart++;
	}
}

void draw_minimap_square(t_main *m, int x, int y, uint32_t color)
{
	int dxStart;
	int dyStart;
	int dxEnd;
	int dyEnd;
	int sqxy;

	sqxy = MINIMAP_WIDTH / m->map.ncols;
	dxStart = MINIMAP_OFFSET + (x * sqxy);
	dxEnd = MINIMAP_OFFSET + (((x + 1) * sqxy) - 1);
	while(dxStart < dxEnd)
	{
		dyStart = MINIMAP_OFFSET + (y * sqxy);
		dyEnd = MINIMAP_OFFSET + (((y + 1) * sqxy) - 1);
		while(dyStart < dyEnd)
		{
			mlx_put_pixel(m->img,  + dxStart, dyStart, color);
			dyStart++;
		}
		dxStart++;
	}
}

// draw walls not walls
void draw_minimap_squares(t_main *m)
{
	int x;
	int y;
	uint32_t color;

	x = 0;
	while(x < m->map.ncols)
	{
		y = 0;
		while(y < m->map.nrows)
		{
			int elem;

			elem = m->map.data_i[y][x];
			if (elem == 0)
			{
				color = MINIMAP_EMPTY_COL; // empty space
			}
			else if (elem == 1)
			{
				color = MINIMAP_WALL_COL; // wall
			}
			draw_minimap_square(m, x, y, color);
			y++;
		}
		x++;
	}
}

void draw_minimap_player_pos(t_main *m)
{
	draw_minimap_square(m, m->pos.y, m->pos.x, MINIMAP_PLAYPOS_COL);
}

void draw_minimap(t_main *m)
{
	// should be a bit translucent
	draw_minimap_window(m);
	draw_minimap_squares(m);
	draw_minimap_player_pos(m);
}
