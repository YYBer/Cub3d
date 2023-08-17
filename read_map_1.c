/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbooth <gbooth@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 09:34:08 by gbooth            #+#    #+#             */
/*   Updated: 2023/08/17 09:43:30 by gbooth           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_map_characters(t_main *m, char *onechar, int *longest_ncols)
{
	while (1)
	{
		if (m->char_read != '0' && m->char_read != '1'
			&& m->char_read != 'N' && m->char_read != 'E'
			&& m->char_read != 'S' && m->char_read != 'W'
			&& m->char_read != ' ' && m->char_read != '\n')
		{
			printf("%s%s%s", ERR_MSG, ERR_FORMAT, ERR_INVALID_MAP_CHAR);
			close(m->fd);
			exit(EXIT_FAILURE);
		}
		if (m->char_read == '\n')
		{
			if (m->map.ncols > *longest_ncols)
				*longest_ncols = m->map.ncols;
			m->map.ncols = 0;
			m->map.nrows++;
		}
		else
			m->map.ncols++;
		if (read(m->fd, onechar, 1) <= 0)
			break ;
		m->char_read = onechar[0];
	}
}

void	get_map_dims(t_main *m)
{
	char	onechar[1];
	int		longest_ncols;

	longest_ncols = 0;
	m->map.nrows = 0;
	m->map.ncols = 0;
	process_map_characters(m, onechar, &longest_ncols);
	m->map.nrows++;
	if (m->map.ncols > longest_ncols)
		longest_ncols = m->map.ncols;
	m->map.ncols = longest_ncols;
	m->map.data_c = NULL;
}

// 'read' re-reads the file
// 'while (i < m->total_chars_read - 1)' seeks to start of map
void	process_row(t_main *m, int row)
{
	int		col;
	bool	shortline_found;
	char	onechar[1];

	shortline_found = false;
	col = 0;
	while (col < m->map.ncols)
	{
		if (shortline_found == false)
		{
			if (read(m->fd, &onechar, 1) == 0)
				shortline_found = true;
			if (col == 0 && onechar[0] == '\n')
				read(m->fd, &onechar, 1);
			if (col > 0 && onechar[0] == '\n')
				shortline_found = true;
		}
		if (shortline_found == false)
			m->map.data_c[row][col] = onechar[0];
		if (shortline_found == true)
			m->map.data_c[row][col] = ' ';
		col++;
	}
}

void	malloc_map_c(t_map *map)
{
	int	i;

	map->data_c = (char **)malloc(map->nrows * sizeof(char *));
	if (map->data_c == NULL)
	{
		printf("%s", ERR_MSG);
		printf("Memory allocation error for row pointers.\n");
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < map->nrows)
	{
		map->data_c[i] = (char *)malloc(map->ncols * sizeof(char));
		if (map->data_c[i] == NULL)
		{
			printf("%s", ERR_MSG);
			printf("Memory allocation error for row %d.\n", i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

void	fill_map(t_main *m)
{
	char	onechar[1];
	int		i;
	int		row;

	m->map.data_alloc = false;
	malloc_map_c(&m->map);
	close(m->fd);
	m->fd = open(m->filename, O_RDONLY);
	if (m->fd == -1)
	{
		printf("%s%s\"%s\"\n", ERR_MSG, ERR_FILE, m->filename);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < m->total_chars_read - 1)
	{
		read(m->fd, &onechar, 1);
		i++;
	}
	row = 0;
	while (row < m->map.nrows)
		process_row(m, row++);
	close(m->fd);
}
