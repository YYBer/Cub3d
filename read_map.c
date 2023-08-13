#include "cub3d.h"

void get_map_dims(t_main *m)
{
    char onechar[1];
    int longest_ncols;

    longest_ncols = 0;
    m->map.nrows = 0;
    m->map.ncols = 0;
    while(read(m->fd, &onechar, 1) > 0)
    {
        if (onechar[0] != '0' && onechar[0] != '1' && 
            onechar[0] != 'N' && onechar[0] != 'E' && 
            onechar[0] != 'S' && onechar[0] != 'W' &&
            onechar[0] != ' ' && onechar[0] != '\n')
        {
            printf("invalid character in map\n");
            close(m->fd);
            // free
            exit(EXIT_FAILURE);
        }
        if (onechar[0] == '\n')
        {
            if (m->map.ncols > longest_ncols)
                longest_ncols = m->map.ncols;
            m->map.ncols = 0;
            m->map.nrows++;
        }
        else
        {
            m->map.ncols++;
        }
    }
    m->map.nrows++;
	if (m->map.ncols > longest_ncols)
		longest_ncols = m->map.ncols;
    m->map.ncols = longest_ncols;
    m->map.data = NULL;
}

void malloc_map(t_map *map)
{
    map->data = (int**)malloc(map->nrows * sizeof(int*));
    if (map->data == NULL)
    {
        printf("Memory allocation error for row pointers.\n");
        exit(EXIT_FAILURE);
    }
    map->data_alloc = true;
    int i;
    i = 0;
    while (i < map->nrows)
    {
        map->data[i] = (int*)malloc(map->ncols * sizeof(int));
        if (map->data[i] == NULL) {
            printf("Memory allocation error for row %d.\n", i);
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void free_map_data(t_map *map)
{
    int i;

    i = 0;
    while (i < map->nrows)
    {
        free(map->data[i]);
        i++;
    }
    free(map->data);
}

void fill_map(t_main *m)
{
    char onechar[1];
    int i;

    m->map.data_alloc = false;
    malloc_map(&m->map);
    close(m->fd);
    m->fd = open(m->filename, O_RDONLY); // re-read
    if (m->fd == -1)
    {
        printf("file error\n");
        exit(EXIT_FAILURE);
    }
    i = 0;
    while(i < m->num_chars_read) // seek to same point as before
    {
        read(m->fd, &onechar, 1);
        i++;
    }
	int row;
	int col;
	bool shortline_found;

	row = 0;
	while(row < m->map.nrows)
	{
		col = 0;
		shortline_found = false;
		while(col < m->map.ncols)
		{
			if (shortline_found == false)
			{
				if (read(m->fd, &onechar, 1) == 0) // end of file reached (if last line is shorter than others)
					shortline_found = true;
				if (col == 0 && onechar[0] == '\n') // skip the newline and read another char
					read(m->fd, &onechar, 1);
				if (col > 0 && onechar[0] == '\n')
				{
					shortline_found = true;
				}
			}
			if (shortline_found == false)
			{
				check_map_position(row, col, m, onechar[0]);
				if (onechar[0] == ' ')
					onechar[0] = '9';
				// printf("%c", onechar[0]);
				m->map.data[row][col] = atoi(onechar);
			}
			if (shortline_found == true)
			{
				// printf("9");
				m->map.data[row][col] = 9;
			}		
			col++;
		}
		// printf("\n");
		row++;
	}
    close(m->fd);
}

void print_map(t_map *map)
{
	int col;
	int row;

	col = 0;
	row = 0;
	while(row < map->nrows)
	{
        col = 0;
		while(col < map->ncols)
		{
			printf("%i", map->data[row][col]);
			col++;
		}
		printf("\n");
		row++;
	}
}
