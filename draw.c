#include "cub3d.h"

// red, green, blue, white, yellow
int	get_wall_color(t_main *m)
{
	int	color;
	int	map_value;

	map_value = m->map.data[m->map_pos.x][m->map_pos.y];
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
	draw_tex2(m, x, drawStart, drawEnd);
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
	int texX = (int)(wallX * TEX_WIDTH);
	if (m->side == 0 && m->raydr.x > 0)
		texX = TEX_WIDTH - texX - 1;
	if (m->side == 1 && m->raydr.y < 0)
		texX = TEX_WIDTH - texX - 1;

	// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
	// How much to increase the texture coordinate per screen pixel
	double step = 1.0 * TEX_HEIGHT / m->lineHeight;
	// Starting texture coordinate
	double texPos = (drawStart - m->pitch - WIN_HEIGHT / 2 + m->lineHeight / 2) * step;

	int y;
	y = drawStart;
	while (y < drawEnd)
	{
		// Cast the texture coordinate to integer, and mask with (TEX_HEIGHT - 1) in case of overflow
		int texY = (int)texPos & (TEX_HEIGHT - 1);
		texPos += step;
		int color = m->textures[0][texX][texY]; // NOTE: eventually need to derive this number from number in map
		//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if(m->side == 1)
			color = (color >> 1) & 8355711;
		mlx_put_pixel(m->img, x, y, color);
		y++;
	}
}

// algorithmically generates a simple cross texture
// left for loops in here as this function will eventually be removed
void generate_textures(t_main *m)
{
	int texNum = 0;

    for (int x = 0; x < TEX_WIDTH; x++)
    {
        for (int y = 0; y < TEX_HEIGHT; y++)
        {
            if (x == y || x == TEX_WIDTH - y)
            {
                m->textures[texNum][x][y] = 0xFF0000FF; // Opaque blue for the cross
            }
            else
            {
                m->textures[texNum][x][y] = 0x00000000; // Black for the rest of the texture
            }
        }
    }
}

// TO CHECK!
int ***create_textures()
{
	int n;
	int i;
	int ***textures;
	
	textures = (int***)malloc(NUM_TEXTURES * sizeof(int**));
    if (textures == NULL)
    {
        printf("Memory allocation error for texture number pointers.\n");
        exit(EXIT_FAILURE);
    }
	n = 0;
	while(n < NUM_TEXTURES)
	{
		textures[n] = (int**)malloc(TEX_HEIGHT * sizeof(int*));
		if (textures[n] == NULL)
		{
			printf("Memory allocation error for row pointers.\n");
			exit(EXIT_FAILURE);
		}
		i = 0;
		while (i < TEX_HEIGHT)
		{
			textures[n][i] = (int*)malloc(TEX_WIDTH * sizeof(int));
			if (textures[n][i] == NULL) {
				printf("Memory allocation error for row %d.\n", i);
				exit(EXIT_FAILURE);
			}
			i++;
		}
	}
    return (textures);
}

void free_textures(int ***textures)
{
	int n;
	int i;

	n = 0;
	while (n < NUM_TEXTURES)
	{
		i = 0;
		while (i < TEX_HEIGHT)
		{
			free(textures[n][i]);
			i++;
		}
		n++;
	}	
    free(textures);
}
