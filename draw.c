#include "cub3d.h"

void draw_floor_ceiling(t_main *m, int x, int drawStart, int drawEnd)
{
    int y;
    y = 0;
	while (y < drawStart)
	{
		mlx_put_pixel(m->img, x, y, m->ceiling_color);
		y++;
	}
    y = drawEnd;
	while (y < WIN_HEIGHT)
	{
		mlx_put_pixel(m->img, x, y, m->floor_color);
		y++;
	}
}

void	draw_tex2(t_main *m, int x, int drawStart, int drawEnd)
{
	//calculate value of wallX
	double wallX; //where exactly the wall was hit
	if (m->side == 0)
		wallX = m->pos.y + m->perp_wall_dist * m->raydr.y;
	else
		wallX = m->pos.x + m->perp_wall_dist * m->raydr.x;
	wallX -= floor((wallX));

	//x coordinate on the texture
	int texX = (int)(wallX * m->textures[m->wall_direction]->width);
	if (m->side == 0 && m->raydr.x > 0)
		texX = m->textures[m->wall_direction]->width - texX - 1;
	if (m->side == 1 && m->raydr.y < 0)
		texX = m->textures[m->wall_direction]->width - texX - 1;

	// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
	// How much to increase the texture coordinate per screen pixel
	double step = 1.0 * m->textures[m->wall_direction]->height / m->lineHeight;
	// Starting texture coordinate
	double texPos = (drawStart - m->pitch - WIN_HEIGHT / 2 + m->lineHeight / 2) * step;

	int y;
	y = drawStart;

	while (y < drawEnd)
	{
		u_int8_t	*pixel;
		// Cast the texture coordinate to integer, and mask with (TEX_HEIGHT - 1) in case of overflow
		int texY = (int)texPos & (m->textures[m->wall_direction]->height - 1);
		texPos += step;
		pixel = &m->textures[m->wall_direction]->pixels[(texX + texY * m->textures[m->wall_direction]->width) * m->textures[m->wall_direction]->bytes_per_pixel];
		int color = pixel[0] << 24 | pixel[1] << 16 | pixel[2] << 8 | pixel[3]; // get colour from pixel
		mlx_put_pixel(m->img, x, y, color);
		y++;
	}
}

void	draw_tex(t_main *m, int x)
{
	//Calculate height of line to draw on screen
	int	drawStart;
	int	drawEnd;

	m->lineHeight = (int)(WIN_HEIGHT / m->perp_wall_dist);
	//calculate lowest and highest pixel to fill in current stripe
	drawStart = -m->lineHeight / 2 + WIN_HEIGHT / 2 + m->pitch;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = m->lineHeight / 2 + WIN_HEIGHT / 2 + m->pitch;
	if (drawEnd >= WIN_HEIGHT)
		drawEnd = WIN_HEIGHT - 1;
	draw_floor_ceiling(m, x, drawStart, drawEnd);
	draw_tex2(m, x, drawStart, drawEnd);
}