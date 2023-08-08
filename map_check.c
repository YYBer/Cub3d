#include "cub3d.h"

int	ft_check_map_command(int argc, char **argv)
{
    size_t i;

	if(argc != 2)
	{
		//printf("wrong number of args\n");
        ft_error("wrong number of args.", NULL);
		return (1);
	}
	i = ft_strlen((const char *)argv[1]);
	if (ft_strnstr(&argv[1][i - 4], ".cub", 4) == NULL)
	{
		//printf("file type is wrong, should be .cub");
        ft_error("file type is wrong, should be .cub", NULL);
		return (1);
	}
	return (0);
}

int ft_map_parameters_check(t_main *m)
{
    int x;
    int y;

    y = 0;
    while (y < m->map.nrows)
    {
        x = 0;
        while (x < m->map.ncols)
        {
            // if (!ft_strchr("01N", m->map.data[y][x]))
            // {
            //     ft_error("wrong parameter0", m);
            //     return (1);
            // }
            if (!x && !y && m->map.data[y][x] == ' ' && m->map.data[y + 1][x] == ' ' && m->map.data[y - 1][x] == ' ' &&
                m->map.data[y][x + 1] == ' ' && m->map.data[y][x - 1] == ' ')
            {
                ft_error("wrong parameter1", m);
                return (1);
            }
            x++;
        }
        y++;
    }
    return (0);
}

// static void	static_test_tile(t_data *data, t_iv pos)
// {
// 	char	c;

// 	c = map_get_at(data->map, pos.x, pos.y);
// 	if (is_in_wall_and_set_player(data, pos, c))
// 	{
// 		if (map_get_at(data->map, pos.x + 1, pos.y) == '\0'
// 			|| map_get_at(data->map, pos.x, pos.y + 1) == '\0'
// 			|| map_get_at(data->map, pos.x - 1, pos.y) == '\0'
// 			|| map_get_at(data->map, pos.x, pos.y - 1) == '\0'
// 			|| map_get_at(data->map, pos.x + 1, pos.y) == ' '
// 			|| map_get_at(data->map, pos.x, pos.y + 1) == ' '
// 			|| map_get_at(data->map, pos.x - 1, pos.y) == ' '
// 			|| map_get_at(data->map, pos.x, pos.y - 1) == ' ')
// 			ft_exit_error("Invalid map.");
// 	}
// 	else if (c != ' ' && c != '1')
// 		ft_exit_error("Invalid map.");
// }



// void	ft_find_map_parameters(t_game *game)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (y < game->map.rows)
// 	{
// 		x = 0;
// 		while (x < game->map.columns)
// 		{
// 			if (!ft_strchr("GEP01S", game->map.full[y][x]))
// 				ft_error("wrong parameter", game);
// 			else if (game->map.full[y][x] == PLAYER)
// 			{
// 				game->map.players++;
// 				game->map.player.x = x * 32;
// 				game->map.player.y = y * 32;
// 			}
// 			else if (game->map.full[y][x] == GOLD)
// 				game->map.gold++;
// 			else if (game->map.full[y][x] == MAP_EXIT)
// 				game->map.exit++;
// 			x++;
// 		}
// 		y++;
// 	}
// }
