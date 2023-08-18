/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:33:43 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/18 17:32:52 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_check_map_command(int argc, char **argv)
{
	size_t	i;

	if (argc < 2 || argc > 3)
		ft_error(ERR_ARGS, NULL);
	if (argc == 3 && ft_strcmp(argv[2], "test") != 0)
		ft_error(ERR_ARGS, NULL);
	i = ft_strlen((const char *)argv[1]);
	if (ft_strnstr(&argv[1][i - 4], ".cub", 4) == NULL)
		ft_error(ERR_FILETYPE, NULL);
}

static int	ft_sc_utils1(char **cmap, int x, int y)
{
	if (cmap[x][y] == ' ' || cmap[x][y] == '\0')
		return (1);
	return (0);
}

static	int	ft_sc_utils2(t_main *m, int x, int y)
{
	return ((ft_sc_utils1(m->map.data_c, x + 1, y)
			+ ft_sc_utils1(m->map.data_c, x - 1, y)
			+ ft_sc_utils1(m->map.data_c, x, y + 1)
			+ ft_sc_utils1(m->map.data_c, x, y - 1)));
}

static int	ft_surround_check_utils3(t_main *m)
{
	int	y;

	y = 0;
	while (y < (int)ft_strlen(m->map.data_c[0]))
	{
		if (m->map.data_c[0][y] == '0')
			return (1);
		y++;
	}
	y = 0;
	while (y < (int)ft_strlen(m->map.data_c[m->map.nrows - 1]))
	{
		if (m->map.data_c[m->map.nrows - 1][y] == '0')
			return (1);
		y++;
	}
	return (0);
}

int	ft_surround_check(t_main *m)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	if (ft_surround_check_utils3(m))
		return (1);
	while (x < m->map.nrows)
	{
		y = 0;
		while (y < (int)ft_strlen(m->map.data_c[x]))
		{
			if (m->map.data_c[x][y] == '0')
			{
				if (y >= (int)(ft_strlen(m->map.data_c[x -1])))
					return (1);
				else if (ft_sc_utils2(m, x, y) > 0)
					return (1);
			}
			y++;
		}
		x++;
	}
	return (0);
}
