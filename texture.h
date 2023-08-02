#ifndef TEXTURE_H
# define TEXTURE_H

# define WALL1 "./texture/wall1.png"
# define WALL2 "./texture/wall2.png"
# define WALL3 "./texture/wall3.png"
# define WALL4 "./texture/wall4.png"
# define FLOOR1 "./texture/floor1.png"
# define FLOOR2 "./texture/floor2.png"
# define FLOOR3 "./texture/floor3.png"
# define FLOOR4 "./texture/floor4.png"
# define CEILING1 "./texture/ceiling1.jpg"
# define CEILING2 "./texture/ceiling2.jpg"
# define GUN "./texture/gun.png"

#endif


// void	place_png_to_img(t_game *game, mlx_image_t **img, char *path)
// {
// 	mlx_texture_t	*my_texture;

// 	my_texture = mlx_load_png(path);
// 	if (!my_texture)
// 		ft_error_and_free_map("wow! texture fucked up.", game);
// 	*img = mlx_texture_to_image(game->mlx, my_texture);
// 	mlx_delete_texture(my_texture);
// 	if (!*img)
// 		ft_error_and_free_map("wow! image fucked up.", game);
// }


// void	init_floor(t_game *game)
// {
// 	place_png_to_img(game, &game->img.floor[0], PNG_FLOOR0);
// 	place_png_to_img(game, &game->img.floor[1], PNG_FLOOR1);
// 	place_png_to_img(game, &game->img.floor[2], PNG_FLOOR2);
// 	place_png_to_img(game, &game->img.floor[3], PNG_FLOOR3);
// 	place_png_to_img(game, &game->img.floor[4], PNG_FLOOR4);
// 	place_png_to_img(game, &game->img.floor[5], PNG_FLOOR5);
// 	place_png_to_img(game, &game->img.floor[6], PNG_FLOOR6);
// 	place_png_to_img(game, &game->img.floor[7], PNG_FLOOR7);
// 	place_png_to_img(game, &game->img.floor[8], PNG_FLOOR8);
// 	place_png_to_img(game, &game->img.floor[9], PNG_FLOOR9);
// 	place_png_to_img(game, &game->img.wall, PNG_WALL);
// 	place_png_to_img(game, &game->img.number[0], PNG_NUM0);
// }