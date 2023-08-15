#include "cub3d.h"

void get_map_dims(t_main *m)
{
    char    onechar[1];
    int     longest_ncols;

    longest_ncols = 0;
    m->map.nrows = 0;
    m->map.ncols = 0;
    while(1)
    {
        if (m->char_read != '0' && m->char_read != '1' && 
            m->char_read != 'N' && m->char_read != 'E' && 
            m->char_read != 'S' && m->char_read != 'W' &&
            m->char_read != ' ' && m->char_read != '\n')
        {
            printf("%s%s%s", ERR_MSG, ERR_FORMAT, ERR_INVALID_MAP_CHAR);
            close(m->fd);
            // free
            exit(EXIT_FAILURE);
        }
        if (m->char_read == '\n')
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
        if (read(m->fd, &onechar, 1) <= 0)
            break;
        m->char_read = onechar[0]; 
    }
    m->map.nrows++;
	if (m->map.ncols > longest_ncols)
		longest_ncols = m->map.ncols;
    m->map.ncols = longest_ncols;
    m->map.data_c = NULL;
}

void malloc_map_c(t_map *map)
{
    map->data_c = (char**)malloc(map->nrows * sizeof(char*));
    if (map->data_c == NULL)
    {
        printf("%s", ERR_MSG);
        printf("Memory allocation error for row pointers.\n");
        exit(EXIT_FAILURE);
    }
    int i;
    i = 0;
    while (i < map->nrows)
    {
        map->data_c[i] = (char*)malloc(map->ncols * sizeof(char));
        if (map->data_c[i] == NULL) {
            printf("%s", ERR_MSG);
            printf("Memory allocation error for row %d.\n", i);
            exit(EXIT_FAILURE);
        }
        i++;
    }
}

void malloc_map_i(t_map *map)
{
    map->data_i = (int**)malloc(map->nrows * sizeof(int*));
    if (map->data_i == NULL)
    {
        printf("%s", ERR_MSG);
        printf("Memory allocation error for row pointers.\n");
        exit(EXIT_FAILURE);
    }
    map->data_alloc = true;
    int i;
    i = 0;
    while (i < map->nrows)
    {
        map->data_i[i] = (int*)malloc(map->ncols * sizeof(int));
        if (map->data_i[i] == NULL) {
            printf("%s", ERR_MSG);
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
        free(map->data_c[i]);
        free(map->data_i[i]);
        i++;
    }
    free(map->data_c);
    free(map->data_i);    
}

void fill_map(t_main *m)
{
    char onechar[1];
    int i;

    m->map.data_alloc = false;
    malloc_map_c(&m->map);
    close(m->fd);
    m->fd = open(m->filename, O_RDONLY); // re-read
    if (m->fd == -1)
    {
        printf("%s%s\"%s\"\n", ERR_MSG, ERR_FILE, m->filename);
        exit(EXIT_FAILURE);
    }
    i = 0;
    while(i < m->total_chars_read - 1) // seek to same point as before (-1 to allow next char to be read below)
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
				check_map_position(row, col, m, onechar[0]); // this can now be done outside this function
				m->map.data_c[row][col] = onechar[0];
			}
			if (shortline_found == true)
			{
				m->map.data_c[row][col] = ' ';
			}		
			col++;
		}
		row++;
	}
    close(m->fd);
}

void print_map_c(t_map *map)
{
	int col;
	int row;

    printf("map.data_c[%i][%i]:\n", map->nrows, map->ncols);	
	col = 0;
	row = 0;
	while(row < map->nrows)
	{
        col = 0;
		while(col < map->ncols)
		{
			printf("%c", map->data_c[row][col]);
			col++;
		}
		printf("\n");
		row++;
	}
}

void print_map_i(t_map *map)
{
	int col;
	int row;

    printf("map.data_i[%i][%i]:\n", map->nrows, map->ncols);	
	col = 0;
	row = 0;
	while(row < map->nrows)
	{
        col = 0;
		while(col < map->ncols)
		{
			printf("%i", map->data_i[row][col]);
			col++;
		}
		printf("\n");
		row++;
	}
}
