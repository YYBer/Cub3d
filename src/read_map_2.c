/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yli <yli@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:34:13 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/17 15:47:44 by yli              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	malloc_map_i(t_main *m)
{
	int		i;
	t_map	*map;

	map = &m->map;
	map->data_i = (int **)malloc(map->nrows * sizeof(int *));
	if (map->data_i == NULL)
		ft_error("Memory allocation error for row pointers.", m);
	map->data_alloc = true;
	i = 0;
	while (i < map->nrows)
	{
		map->data_i[i] = (int *)malloc(map->ncols * sizeof(int));
		if (map->data_i[i] == NULL)
			ft_error("Memory allocation error for row.", m);
		i++;
	}
}

// converts ' ' to 0 for now (in the end better if -1)
void	convert_map_data_c_to_i(t_main *m)
{
	int		col;
	int		row;
	char	c;

	malloc_map_i(m);
	row = 0;
	while (row < m->map.nrows)
	{
		col = 0;
		while (col < m->map.ncols)
		{
			c = m->map.data_c[row][col];
			if (c == 'N' || c == 'S' || c == 'W' || c == 'E' || c == ' ')
				m->map.data_i[row][col] = 0;
			else
				m->map.data_i[row][col] = c - '0';
			col++;
		}
		row++;
	}
}
