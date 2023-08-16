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
                
                {
                    ft_error("the map is not completely closed!", m);
                    return (1);
                }
            }
            y++;
        }
        x++;
    }
    return (0);
}