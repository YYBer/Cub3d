#include "cub3d.h"

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
		int color = m->textures[m->side][texX][texY];
		mlx_put_pixel(m->img, x, y, color);
		y++;
	}
}

// algorithmically generates a simple cross texture
// left for loops in here as this function will eventually be removed
void generate_textures(t_main *m) {
    for (int x = 0; x < TEX_WIDTH; x++) {
        for (int y = 0; y < TEX_HEIGHT; y++) {
            if (x == y || x == TEX_WIDTH - y) {
                m->textures[0][x][y] = 0xFF0000FF; // Red color
            } else {
                m->textures[0][x][y] = 0x000000FF; // Transparent (black) color
            }

            // Extra Texture 1: Sloped Greyscale
            int xycolor = (x + y) / 2;
            m->textures[1][x][y] = 0xAA0000FF | (xycolor + 256 * xycolor + 65536 * xycolor);

            // Extra Texture 2: Sloped Yellow Gradient
            m->textures[2][x][y] = 0x00AA00FF | (256 * xycolor + 65536 * xycolor);

            // Extra Texture 3: XOR Greyscale
            int xorcolor = x ^ y;
            m->textures[3][x][y] = 0x0000AAFF | (xorcolor + 256 * xorcolor + 65536 * xorcolor);
        }
    }
}

int*** create_textures()
{
    int*** textures = (int***)malloc(NUM_TEXTURES * sizeof(int**));
    if (textures == NULL) {
        printf("Memory allocation error for texture array pointers.\n");
        exit(EXIT_FAILURE);
    }

    for (int n = 0; n < NUM_TEXTURES; n++) {
        textures[n] = (int**)malloc(TEX_HEIGHT * sizeof(int*));
        if (textures[n] == NULL) {
            printf("Memory allocation error for row pointers of texture %d.\n", n);
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < TEX_HEIGHT; i++) {
            textures[n][i] = (int*)malloc(TEX_WIDTH * sizeof(int));
            if (textures[n][i] == NULL) {
                printf("Memory allocation error for row %d of texture %d.\n", i, n);
                exit(EXIT_FAILURE);
            }
        }
    }

    return textures;
}

void free_textures(int*** textures)
{
    for (int n = 0; n < NUM_TEXTURES; n++) {
        for (int i = 0; i < TEX_HEIGHT; i++) {
            free(textures[n][i]);
        }
        free(textures[n]);
    }
    free(textures);
}
