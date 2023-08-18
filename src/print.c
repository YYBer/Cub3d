/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:34:03 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/18 10:47:52 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	print_rgba(int value)
{
	int	red;
	int	green;
	int	blue;
	int	alpha;

	red = (value >> 24) & 0xFF;
	green = (value >> 16) & 0xFF;
	blue = (value >> 8) & 0xFF;
	alpha = value & 0xFF;
	printf("0x%02X%02X%02X%02X", red, green, blue, alpha);
}

void	print_cub_file_summary(t_main *m)
{
	printf("--Printing .cub file summary:\n");
	printf("texture path 0: \"%s\"\n", m->tex_paths[0]);
	printf("texture path 1: \"%s\"\n", m->tex_paths[1]);
	printf("texture path 2: \"%s\"\n", m->tex_paths[2]);
	printf("texture path 3: \"%s\"\n", m->tex_paths[3]);
	printf("floor color:		");
	print_rgba(m->floor_color);
	printf("\n");
	printf("ceiling color:	");
	print_rgba(m->ceiling_color);
	printf("\n");
	print_map_c(&m->map);
	print_map_i(&m->map);
}

void	print_map_c(t_map *map)
{
	int	col;
	int	row;

	printf("map.data_c[%i][%i]:\n", map->nrows, map->ncols);
	col = 0;
	row = 0;
	while (row < map->nrows)
	{
		col = 0;
		while (col < map->ncols)
		{
			printf("%c", map->data_c[row][col]);
			col++;
		}
		printf("\n");
		row++;
	}
}

void	print_map_i(t_map *map)
{
	int	col;
	int	row;

	printf("map.data_i[%i][%i]:\n", map->nrows, map->ncols);
	col = 0;
	row = 0;
	while (row < map->nrows)
	{
		col = 0;
		while (col < map->ncols)
		{
			printf("%i", map->data_i[row][col]);
			col++;
		}
		printf("\n");
		row++;
	}
}
