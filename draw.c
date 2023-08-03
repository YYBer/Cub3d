#include "cub3d.h"

int wm[24][24] = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,1,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,1},
	{1,0,0,0,0,0,4,4,4,4,4,4,4,4,4,0,0,0,0,5,0,0,0,1},
	{1,0,0,0,0,0,4,0,0,0,0,0,0,0,4,0,0,0,0,4,0,0,0,1},
	{1,4,4,0,4,4,4,0,4,4,4,4,4,0,4,0,0,0,0,3,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,4,0,4,0,4,0,0,0,0,0,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,0,4,0,4,0,4,0,0,0,0,3,0,0,0,1},
	{1,4,0,4,0,0,0,0,4,0,4,0,4,0,4,0,0,0,0,4,0,0,0,1},
	{1,4,0,0,0,0,4,0,4,0,4,0,4,0,4,0,0,0,0,5,0,0,0,1},
	{1,4,0,4,0,4,2,0,4,0,0,0,4,0,4,0,0,0,0,4,0,0,0,1},
	{1,4,0,4,4,4,4,4,4,4,4,4,4,0,4,0,0,0,0,3,0,0,0,1},
	{1,4,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,2,0,0,0,1},
	{1,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,1,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

// red, green, blue, white, yellow
int	get_wall_color(t_main *m)
{
	int	color;
	int	map_value;

	map_value = m->world_map[m->map.x][m->map.y];
	if (map_value == 1)
		color = COLOUR_RED;
	else if (map_value == 2)
		color = COLOUR_BLUE;
	else if (map_value == 3)
		color = COLOUR_GREEN;
	else if (map_value == 4)
		color = COLOUR_WHITE;
	else
		color = COLOUR_YELLOW;
	return (color);
}

void	ver_line(mlx_image_t *img, int x, int y1, int y2, int color)
{
	int	y;

	y = y1;
	while (y <= y2)
	{
		mlx_put_pixel(img, x, y, color);
		y++;
	}
}

void	draw_ver_line(t_main *m, int x)
{
	//Calculate height of line to draw on screen
	int	lineHeight;
	int	drawStart;
	int	drawEnd;
	int	color;

	lineHeight = (int)(WIN_HEIGHT / m->perp_wall_dist);
	//calculate lowest and highest pixel to fill in current stripe
	drawStart = -lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawStart < 0)
		drawStart = 0;
	drawEnd = lineHeight / 2 + WIN_HEIGHT / 2;
	if (drawEnd >= WIN_HEIGHT)
		drawEnd = WIN_HEIGHT - 1;
	// get wall colour
	color = get_wall_color(m);
	//give x and y sides different brightness
	if (m->side == 1)
	// 	color = color / 2;
		color = (color >> 1) & 8355711; // make a bit darker
	//draw the pixels of the stripe as a vertical line
	ver_line(m->img, x, drawStart, drawEnd, color);
}