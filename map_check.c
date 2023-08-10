#include "cub3d.h"

int	ft_check_map_command(int argc, char **argv)
{
    size_t i;

	if(argc != 2)
	{
        ft_error("wrong number of args.", NULL);
		return (1);
	}
	i = ft_strlen((const char *)argv[1]);
	if (ft_strnstr(&argv[1][i - 4], ".cub", 4) == NULL)
	{
        ft_error("file type is wrong, should be .cub", NULL);
		return (1);
	}
	return (0);
}

// void print_map(t_map *map)
// {
// 	int col;
// 	int row;

// 	col = 0;
// 	row = 0;
// 	while(row < map->nrows)
// 	{
//         col = 0;
// 		while(col < map->ncols)
// 		{
// 			printf("%i", map->data[row][col]);
// 			col++;
// 		}
// 		printf("\n");
// 		row++;
// 	}
// }

static int  ft_surround_check(t_map map)
{
	int col;
	int row;

	col = 0;
	row = 0;
    while (row < map.nrows)
    {
        if (map.data[row][0] != 1 || map.data[row][map.ncols - 1] != 1)
            return (1);
        row++;
    }
    while (col < map.ncols)
    {
        if (map.data[0][col] != 1 || map.data[map.nrows - 1][col] != 1)
            return (1);
        col++;
    }
    return (0);
}

int ft_map_parameters_check(t_main *m)
{
    int x;
    int y;

    y = 0;
    if (ft_surround_check(m->map))
    {
        ft_error("wrong parameter0", m);
        return (1);
    }
    while (y < m->map.nrows)
    {
        x = 0;
        while (x < m->map.ncols)
        {
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