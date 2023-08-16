#include "cub3d.h"

int	ft_check_map_command(int argc, char **argv)
{
    size_t i;

    (void)argc;
	if(argc != 2 || (argc == 3 && strcmp(argv[2], "test") == 0))
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

static int ft_surround_check_utils(char **cmap, int x, int y)
{
    if (cmap[x][y] == ' ' || cmap[x][y] == '\0')
        return (1);
    return (0);
}

int ft_surround_check(t_main *m)
{
    int x;
    int y;

    x = 0;
    while (x < m->map.nrows)
    {
        y = 0;
        while (y < (int)ft_strlen(m->map.data_c[x]))
        {
            if (m->map.data_c[x][y] == '0')
            {
                if ((ft_surround_check_utils(m->map.data_c, x + 1, y)
                        + ft_surround_check_utils(m->map.data_c, x - 1, y) 
                            + ft_surround_check_utils(m->map.data_c, x, y + 1) 
                                + ft_surround_check_utils(m->map.data_c, x, y - 1)) > 0)
                    return (1);
            }
            y++;
        }
        x++;
    }
    return (0);
}

// static int  ft_surround_check(t_map map)
// {
// 	int col;
// 	int row;

// 	col = 0;
// 	row = 0;
//     while (row < map.nrows)
//     {
//         if (map.data_i[row][0] != 1 || map.data_i[row][map.ncols - 1] != 1)
//             return (1);
//         row++;
//     }
//     while (col < map.ncols)
//     {
//         if (map.data_i[0][col] != 1 || map.data_i[map.nrows - 1][col] != 1)
//             return (1);
//         col++;
//     }
//     return (0);
// }

// int ft_map_parameters_check(t_main *m)
// {
//     int x;
//     int y;

//     y = 0;
//     if (ft_surround_check(m->map))
//     {
//         ft_error("wrong parameter0", m);
//         return (1);
//     }
//     while (y < m->map.nrows)
//     {
//         x = 0;
//         while (x < m->map.ncols)
//         {
//             if (!x && !y && m->map.data_c[y][x] == ' ' && m->map.data_c[y + 1][x] == ' ' && m->map.data_c[y - 1][x] == ' ' &&
//                 m->map.data_c[y][x + 1] == ' ' && m->map.data_c[y][x - 1] == ' ')
//             {
//                 ft_error("wrong parameter1", m);
//                 return (1);
//             }
//             x++;
//         }
//         y++;
//     }
//     return (0);
// }