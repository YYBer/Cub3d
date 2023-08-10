// TODO: remove use of exit
// TODO: handle maps with blank space at start of lines
// TODO: handle maps with irregular number of rows/cols

// how it works right now:
// - lines can consist of \n, blank space, or digits from 0 to 4

#include "cub3d.h"

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

void check_map_position(int x, int y, t_main *m)
{
    printf("xy: %i %i\n", x, y);
    printf("mc: %c\n", m->map.data[x][y]);
    if (m->map.data[x][y] == 'N' || m->map.data[x][y] == 'S' || m->map.data[x][y] == 'W' || m->map.data[x][y] == 'E')
    {
        printf("here!\n");
        m->pos.x = x;
        m->pos.y = y;
    }
    if (m->map.data[x][y] == 'N')
    {
        printf("N!\n");
        m->dir.x = 0;
        m->dir.y = -1;
        m->plane.x = 0.66;
        m->plane.y = 0;
    }
    if (m->map.data[x][y] == 'S')
    {
        printf("S!\n");
        m->dir.x = 0;
        m->dir.y = 1;
        m->plane.x = -0.66;
        m->plane.y = 0;		               
    }
    if (m->map.data[x][y] == 'W')
    {
        printf("W!\n");
        m->dir.x = -1;
        m->dir.y = 0;
        m->plane.x = 0;
        m->plane.y = -0.66;                
    }
    if (m->map.data[x][y] == 'E')
    {
        printf("E!\n");
        m->dir.x = 1;
        m->dir.y = 0;
        m->plane.x = 0;
        m->plane.y = 0.66;                
    }
}