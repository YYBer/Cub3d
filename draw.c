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
      int texNum = wm[m->map.x][m->map.y] - 1; //1 subtracted from it so that texture 0 can be used!

      //calculate value of wallX
      double wallX; //where exactly the wall was hit
      if(m->side == 0) wallX = m->pos.y + m->perp_wall_dist * m->raydr.y;
      else          wallX = m->pos.x + m->perp_wall_dist * m->raydr.x;
      wallX -= floor((wallX));

      //x coordinate on the texture
      int texX = (int)(wallX * TEX_WIDTH);
      if(m->side == 0 && m->raydr.x > 0) texX = TEX_WIDTH - texX - 1;
      if(m->side == 1 && m->raydr.y < 0) texX = TEX_WIDTH - texX - 1;

      // TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
      // How much to increase the texture coordinate per screen pixel
      double step = 1.0 * TEX_HEIGHT / m->lineHeight;
      // Starting texture coordinate
      double texPos = (drawStart - m->pitch - WIN_HEIGHT / 2 + m->lineHeight / 2) * step;
      for(int y = drawStart; y < drawEnd; y++)
      {
        // Cast the texture coordinate to integer, and mask with (TEX_HEIGHT - 1) in case of overflow
        int texY = (int)texPos & (TEX_HEIGHT - 1);
        texPos += step;
        int color = m->texture[texNum][TEX_HEIGHT * texY + texX];
        //make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
        if(m->side == 1) color = (color >> 1) & 8355711;
		mlx_put_pixel(m->img, x, y, color);
      }
}

// this is probably not calculating the kind of colours we need
void  generate_textures(t_main *m)
{
  for(int x = 0; x < TEX_WIDTH; x++)
  for(int y = 0; y < TEX_HEIGHT; y++)
  {
    // int xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
    //int xcolor = x * 256 / TEX_WIDTH;
    // int ycolor = y * 256 / TEX_HEIGHT;
    // int xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
    m->texture[x][TEX_WIDTH * y] = 65536 * 254 * (x != y && x != TEX_WIDTH - y); //flat red texture with black cross
    // texture[1][TEX_WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
    // texture[2][TEX_WIDTH * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
    // texture[3][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
    // texture[4][TEX_WIDTH * y + x] = 256 * xorcolor; //xor green
    // texture[5][TEX_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
    // texture[6][TEX_WIDTH * y + x] = 65536 * ycolor; //red gradient
    // texture[7][TEX_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey texture
  }
}

int** create_2d_array() {
    int** array = (int**)malloc(TEX_HEIGHT * sizeof(int*));
    if (array == NULL) {
        printf("Memory allocation error for row pointers.\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < TEX_HEIGHT; i++) {
        array[i] = (int*)malloc(TEX_WIDTH * sizeof(int));
        if (array[i] == NULL) {
            printf("Memory allocation error for row %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }

    return array;
}

void free_2d_array(int** array) {
    for (int i = 0; i < TEX_HEIGHT; i++) {
        free(array[i]);
    }
    free(array);
}
