// TODO: remove use of exit
// TODO: handle maps with blank space at start of lines
// TODO: handle maps with irregular number of rows/cols

// how it works right now:
// - lines can consist of \n, blank space, or digits from 0 to 4

#include "cub3d.h"

// __fortify_function __wur ssize_t
// read (int __fd, void *__buf, size_t __nbytes)
// {
//   return __glibc_fortify (read, __nbytes, sizeof (char),
// 			  __glibc_objsize0 (__buf),
// 			  __fd, __buf, __nbytes);
// }
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
        if ((onechar[0] < '0' || onechar[0] > '1') && 
            onechar[0] != 'N' && onechar[0] != 'E' && onechar[0] != 'S' && onechar[0] != 'W' &&
                onechar[0] != '\n')
        {
            printf("invalid character in map\n");
            close(fd);
            // free
            exit(EXIT_FAILURE);
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
    map->data = (char**)malloc(map->nrows * sizeof(char*));
    if (map->data == NULL)
    {
        printf("Memory allocation error for row pointers.\n");
        exit(EXIT_FAILURE);
    }
    int i;
    i = 0;
    while (i < map->nrows)
    {
        map->data[i] = (char*)malloc(map->ncols * sizeof(char));
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
			printf("%i", map->data[row][col]);
			col++;
		}
		printf("\n");
		row++;
	}
}
