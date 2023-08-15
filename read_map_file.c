#include "cub3d.h"

void read_subject_file(char **argv, t_main *m)
{
   	m->filename = argv[1];
	m->total_chars_read = 0; 
    m->fd = open(m->filename, O_RDONLY);
    if (m->fd == -1)
    {
        printf("%s%s", ERR_MSG, ERR_FILE);
        exit(EXIT_FAILURE);
    }
	init_fileflags(m);
	read_prefixes(m);
	read_prefixes(m);	
	read_prefixes(m);
	read_prefixes(m);
	read_prefixes(m);
	read_prefixes(m);
    while (m->char_read == '\n') // skip newlines
       read_char(m);
}

void check_map_position(int x, int y, t_main *m, char map_char)
{
    if (map_char == 'N' || map_char == 'S' || map_char == 'W' || map_char == 'E')
    {
        m->pos.x = x;
        m->pos.y = y;
    }
    if (map_char == 'N')
    {
        m->dir.x = 1;
        m->dir.y = 0;
        m->plane.x = 0;
        m->plane.y = 0.66;        
    }
    if (map_char == 'S')
    {
        m->dir.x = -1;
        m->dir.y = 0;
        m->plane.x = 0;
        m->plane.y = -0.66;                             
    }
    if (map_char == 'W')
    {
        m->dir.x = 0;
        m->dir.y = -1;
        m->plane.x = 0.66;
        m->plane.y = 0;                  
    }
    if (map_char == 'E')
    {
        m->dir.x = 0;
        m->dir.y = 1;
        m->plane.x = -0.66;
        m->plane.y = 0;
    }
}