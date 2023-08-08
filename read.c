// TODO: remove use of exit
// TODO: handle maps with blank space at start of lines
// TODO: handle maps with irregular number of rows/cols

// how it works right now:
// - lines can consist of \n, blank space, or digits from 0 to 4

#include "cub3d.h"

t_map get_map_dims(char *filename)
{
    t_map map;
    int fd;
    char onechar[1];
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("file error\n");
        exit(EXIT_FAILURE);
    }
    map.nrows = 0;
    map.ncols = 0;
    while(read(fd, &onechar, 1) > 0)
    {
        if ((onechar[0] < '0' || onechar[0] > '5') && onechar[0] != '\n')
        {
            map.nrows = -1;
            map.ncols = -1;
            break;
        }
        if (onechar[0] == '\n')
        {
            map.ncols = 0;
            map.nrows++;
        }
        else
        {
            map.ncols++;
        }
    }
    map.nrows++;
    close(fd);
    map.data = NULL;
    return(map);
}

void malloc_map(t_map *map)
{
    map->data = (int**)malloc(map->nrows * sizeof(int*));
    if (map->data == NULL)
    {
        printf("Memory allocation error for row pointers.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < map->nrows; i++)
    {
        map->data[i] = (int*)malloc(map->ncols * sizeof(int));
        if (map->data[i] == NULL) {
            printf("Memory allocation error for row %d.\n", i);
            exit(EXIT_FAILURE);
        }
    }
}

void free_map_data(t_map *map)
{
    for (int i = 0; i < map->nrows; i++)
    {
        free(map->data[i]);
    }
    free(map->data);
}

void fill_map(t_map *map, char *filename)
{
    int fd;
    char onechar[1];

    malloc_map(map);
    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("file error\n");
        exit(EXIT_FAILURE);
    }
    int col = 0;
    int row = 0;
    while(row < map->nrows)
    {
        col = 0;
        while(col < map->ncols)
        {
            if (read(fd, &onechar, 1) < 1)
            {
                printf("read error\n");
                exit(EXIT_FAILURE);
            }
            map->data[row][col] = atoi(onechar); // REPLACE WITH ft_atoi // rewrite to be x, y
            col++;
        }
        read(fd, &onechar, 1); // read the newline char but don't use it
        row++;
    }
    close(fd);
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
			printf("%i", map->data[row][col]); // REPLACE WITH ft_printf
			col++;
		}
		printf("\n"); // REPLACE WITH ft_printf
		row++;
	}
}
