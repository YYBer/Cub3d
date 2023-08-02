// gcc mlx42-test.c MLX42/build/libmlx42.a -IMLX42/include/MLX42 -ldl -lglfw -pthread -lm

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "MLX42.h"
#define WIDTH 256
#define HEIGHT 256

// Exit the program as failure.
static void ft_error(void)
{
	fprintf(stderr, "%s", mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}

void verLine(mlx_image_t *img, int x, int y1, int y2, int color)
{
	(void)color;
    for (int y = y1; y <= y2; y++)
    {
        mlx_put_pixel(img, x, y, 0xFF0000FF);
    }
}

// Print the window width and height.
static void ft_hook(void* param)
{
	mlx_image_t* img = param;

	verLine(img, 10, 0, 10, 0xFF000000);
}

int32_t	main(void)
{
	// MLX allows you to define its core behaviour before startup.
	mlx_set_setting(MLX_MAXIMIZED, false);
	mlx_t* mlx = mlx_init(WIDTH, HEIGHT, "42Balls", true);
	if (!mlx)
		ft_error();

	/* Do stuff */

	// Create and display the image.
	mlx_image_t* img = mlx_new_image(mlx, 256, 256);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error();

	// Register a hook and pass mlx as an optional param.
	// NOTE: Do this before calling mlx_loop!
	mlx_loop_hook(mlx, ft_hook, img);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (EXIT_SUCCESS);
}