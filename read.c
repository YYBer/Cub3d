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

// modify to work with fd
t_map get_map_dims(int fd)
{
    t_map map;
    char onechar[1];

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
    map->data_alloc = true;
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

void fill_map(int fd, t_map *map, char *filename)
{
    char onechar[1];

    

    map->data_alloc = false;
    malloc_map(map);
    close(fd);
    // close fd, reopen file and seek to same point
    // keep a read count
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
            map->data[row][col] = atoi(onechar); // REPLACE WITH ft_atoi
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


//

void read_wall_tex_path(int fd)
{
    char onechar[1];
    char   path_str[PATH_MAX];
    int     i;

    i = 0;
    while(1)
    {
        if (read(fd, &onechar, 1) < 1)
        {
            printf("file error\n");
            exit(EXIT_FAILURE);
        }
        if (onechar[0] == '\n')
            break;
        path_str[i] = onechar[0];
        i++;
    }
    path_str[i] = '\0';
    printf("path is: %s\n", path_str);
}

int read_wall_tex_prefix(int fd, char *prefix)
{
    char onechar[1];
    int i;
    char tofind;

    i = 0;
    while(i < 3)
    {
        if (read(fd, &onechar, 1) < 1)
        {
            printf("file error\n");
            exit(EXIT_FAILURE);
        }
        if (i == 2)
            tofind = ' ';
        else
            tofind = prefix[i];
        if (onechar[0] != tofind)
            return (1);
        i++;
    }
    return (0);
}

void read_tex_filenames(int fd)
{
    char    *prefix[4];
    int     i;

    prefix[0] = "NO";
    prefix[1] = "SO";
    prefix[2] = "WE";
    prefix[3] = "EA";
    i = 0;
    while(i < 4)
    {
        if (read_wall_tex_prefix(fd, prefix[i]))
        {
            printf("invalid map format\n");
            exit(EXIT_FAILURE);
        }
        read_wall_tex_path(fd);
        i++;
    }
}

int read_color_value(int fd, char *onecharbuf)
{    
    char    onechar[1];
    char    color_str[PATH_MAX]; 
    int     i;
    bool    non_digit_found;

    non_digit_found = false;
    i = 0;
    while(non_digit_found == false)
    {
        if (read(fd, &onechar, 1) < 1)
        {
            printf("file error\n");
            exit(EXIT_FAILURE);
        }
        if (onechar[0] < '0' || onechar[0] > '9') // if non-digit found
        {
            if (i == 0) // if no digits have been read previously, map format is invalid
            {
                printf("invalid map format\n");
                exit(EXIT_FAILURE);
            }                        
            else // if digits been red previously, stop searching and go on in the program
            {
                *onecharbuf = onechar[0];
                non_digit_found = true;
            }
        }
        else
        {
            color_str[i] = onechar[0];
            i++;
        }
    }
    color_str[i] = '\0';
    return (atoi(color_str)); // convert to ft_atoi!
}

void read_char(int fd, char tofind)
{
    char onechar[1];

    if (read(fd, &onechar, 1) < 1)
    {
        printf("file error\n");
        exit(EXIT_FAILURE);
    }
    if (onechar[0] != tofind)
    {
        printf("invalid map format\n");
        exit(EXIT_FAILURE);
    }
}

void read_charbuf(char onecharbuf, char tofind)
{
    if (onecharbuf != tofind)
    {
        printf("invalid map format\n");
        exit(EXIT_FAILURE);
    }
}

int read_floor_ceiling_color(int fd, char floor_ceiling)
{
    int     red;
    int     green;
    int     blue;
    char    onecharbuf;

    read_char(fd, floor_ceiling);
    read_char(fd, ' ');
    red = read_color_value(fd, &onecharbuf);
    printf("red val:%i\n", red);
    read_charbuf(onecharbuf, ',');
    green = read_color_value(fd, &onecharbuf);
    printf("green val:%i\n", green);
    read_charbuf(onecharbuf, ',');
    blue = read_color_value(fd, &onecharbuf);
    printf("blue val:%i\n", blue);
    read_charbuf(onecharbuf, '\n');
    return ((0xFF << 24) | (red << 16) | (green << 8) | blue);
}

int open_subject_file(char *filename)
{
    int     fd;

    fd = open(filename, O_RDONLY);
    if (fd == -1)
    {
        printf("file error\n");
        exit(EXIT_FAILURE);
    }
    return (fd); 
}

void read_subject_file(t_main *m)
{
    read_tex_filenames(m->fd);
    m->floor_color = read_floor_ceiling_color(m->fd, 'F');
    printf("floor_color val:%i\n\n", m->floor_color);
    m->ceiling_color = read_floor_ceiling_color(m->fd, 'C');
    printf("ceiling_color val:%i\n\n", m->ceiling_color);
    // read two more newlines to get us up to part where we accept world map
    read_char(m->fd, '\n');
    read_char(m->fd, '\n');
}