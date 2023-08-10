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

// reading map

// modify to work with fd
void get_map_dims(t_main *m)
{
    char onechar[1];

    m->map.nrows = 0;
    m->map.ncols = 0;
    while(read(m->fd, &onechar, 1) > 0)
    {
        if ((onechar[0] < '0' || onechar[0] > '1') && 
            onechar[0] != 'N' && onechar[0] != 'E' && onechar[0] != 'S' && onechar[0] != 'W' &&
                onechar[0] != '\n')
        {
            printf("invalid character in map\n");
            close(m->fd);
            // free
            exit(EXIT_FAILURE);
        }
        if (onechar[0] == '\n')
        {
            m->map.ncols = 0;
            m->map.nrows++;
        }
        else
        {
            m->map.ncols++;
        }
    }
    m->map.nrows++;
    m->map.data = NULL;
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
            m->map.data[row][col] = atoi(onechar); // REPLACE WITH ft_atoi
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

// reading textures

char *read_wall_tex_path(t_main *m)
{
    char onechar[1];
    char   path_str[PATH_MAX];
    int     i;

    i = 0;
    while(1)
    {
        if ((m->num_chars_read += read(m->fd, &onechar, 1)) < 1)
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
    return(strdup(path_str)); // change to ft_strdup and don't forget to free
}

int read_wall_tex_prefix(t_main *m, char *prefix)
{
    char onechar[1];
    int i;
    char tofind;

    i = 0;
    while(i < 3)
    {
        if ((m->num_chars_read += read(m->fd, &onechar, 1)) < 1)
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

void read_tex_filenames(t_main *m)
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
        if (read_wall_tex_prefix(m, prefix[i]))
        {
            printf("invalid map format\n");
            exit(EXIT_FAILURE);
        }
        m->tex_paths[i] = read_wall_tex_path(m);
        i++;
    }
}

int read_color_value(t_main *m, char *onecharbuf)
{    
    char    onechar[1];
    char    color_str[PATH_MAX]; 
    int     i;
    bool    non_digit_found;

    non_digit_found = false;
    i = 0;
    while(non_digit_found == false)
    {
        if ((m->num_chars_read += read(m->fd, &onechar, 1)) < 1)
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

void read_char(t_main *m, char tofind)
{
    char onechar[1];

    if ((m->num_chars_read += read(m->fd, &onechar, 1)) < 1)
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

int read_floor_ceiling_color(t_main *m, char floor_ceiling)
{
    int     red;
    int     green;
    int     blue;
    char    onecharbuf;

    read_char(m, floor_ceiling);
    read_char(m, ' ');
    red = read_color_value(m, &onecharbuf);
    read_charbuf(onecharbuf, ',');
    green = read_color_value(m, &onecharbuf);
    read_charbuf(onecharbuf, ',');
    blue = read_color_value(m, &onecharbuf);
    read_charbuf(onecharbuf, '\n');
    return ((red << 24) | (green << 16) | (blue << 8) | 0xFF);
}

void read_subject_file(char **argv, t_main *m)
{
   	m->filename = argv[1];
	m->num_chars_read = 0; 
    m->fd = open(m->filename, O_RDONLY);
    if (m->fd == -1)
    {
        printf("file error\n");
        exit(EXIT_FAILURE);
    }
    read_tex_filenames(m);
    m->floor_color = read_floor_ceiling_color(m, 'F');
    m->ceiling_color = read_floor_ceiling_color(m, 'C');
    // read any number of newlines to get us up to part where we accept world map
    read_char(m, '\n');
    read_char(m, '\n');
}

void load_textures(t_main *m)
{
    printf("0: \"%s\"\n", m->tex_paths[0]);
    printf("1: \"%s\"\n", m->tex_paths[1]);
    printf("2: \"%s\"\n", m->tex_paths[2]);
    printf("3: \"%s\"\n", m->tex_paths[3]);
    m->textures[0] = mlx_load_png(m->tex_paths[0]);
    m->textures[1] = mlx_load_png(m->tex_paths[1]);
    m->textures[2] = mlx_load_png(m->tex_paths[2]);
    m->textures[3] = mlx_load_png(m->tex_paths[3]);
}

void delete_textures(t_main *m)
{
    mlx_delete_texture(m->textures[0]);
	mlx_delete_texture(m->textures[1]);
	mlx_delete_texture(m->textures[2]);
	mlx_delete_texture(m->textures[3]);
}