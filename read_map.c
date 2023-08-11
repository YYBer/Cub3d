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
            onechar[0] != '\n')
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
    m->map.ncols = longest_ncols;
    m->map.data = NULL;
}

static void malloc_map2(t_map *map)
{
    int i;

    i = 0;
    map->data = (int**)malloc(map->nrows * sizeof(int*));
    if (map->data == NULL)
    {
        printf("Memory allocation error for row pointers.\n");
        exit(EXIT_FAILURE);
    }
    map->data_alloc = true;
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

// #include <stdio.h>
// int main()
// {
// 	int fd = open("map.cub", O_RDONLY);
// 	char *wbuffer = get_next_line(fd);
// 	while (wbuffer)
// 	{
// 		printf("%s", wbuffer);
// 		free(wbuffer);
// 		wbuffer = get_next_line(fd);
// 	}
// 	close(fd);
// 	return (0);
// }


void    malloc_map(t_main *m)
{
    char *wbuffer;
    char *wmap;

    wmap = ft_strdup("");
    m->fd = open(m->filename, O_RDONLY);
    if (m->fd < 0)
        ft_error("open map failed", m);
    while (1)
    {
        wbuffer = get_next_line(m->fd);
        if (wbuffer == NULL)
            break ;
        wmap = ft_strjoin_free1(wmap, wbuffer);
        m->map.ncols = ft_strlen(wbuffer) - 1;
        free(wbuffer);
        m->map.nrows++;
    }
    close(m->fd);
    m->map.cmap = ft_split(wmap, '\n');
    // printf("%s", m->map.cmap[0]);
    // printf("%s", m->map.cmap[1]);
    // printf("%s", m->map.cmap[3]);
    printf("wmap: %s\n", wmap);
    free(wmap);
    m->map.cmap_alloc = true;
    malloc_map2(&m->map);
    print_map(&m->map);
}

// void	ft_init_map(t_game *game, char **argv)
// {
// 	char	*wbuffer;
// 	char	*wmap;

// 	game->fd = open(argv[1], O_RDONLY);
// 	game->map.rows = 0;
// 	if (game->fd < 0)
// 		ft_error("can't read the map", game);
// 	wmap = ft_strdup("");
// 	while (true)
// 	{
// 		wbuffer = get_next_line(game->fd);
// 		if (wbuffer == NULL)
// 			break ;
// 		wmap = ft_strjoin_frees1(wmap, wbuffer);
// 		game->map.columns = ft_strlen(wbuffer) - 1;
// 		free(wbuffer);
// 		game->map.rows++;
// 	}
// 	printf("in map init = %d\n", game->map.columns);
// 	close(game->fd);
// 	game->map.full = ft_split(wmap, '\n');
// 	free(wmap);
// 	game->map_alloc = true;
// }

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
    m->map.cmap_alloc = false;
    malloc_map(m);
    //close(m->fd);
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
    int col = 0;
    int row = 0;
    while(row < m->map.nrows)
    {
        col = 0;
        while(col < m->map.ncols)
        {
            if (read(m->fd, &onechar, 1) < 1)
            {
                printf("read error\n");
                exit(EXIT_FAILURE);
            }
            check_map_position(row, col, m, onechar[0]);
            m->map.data[row][col] = atoi(onechar);
            col++;
        }
        read(m->fd, &onechar, 1); // read the newline char but don't use it
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
    printf("---------------start--------------\n");
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
    printf("---------------end----------------\n");
}
