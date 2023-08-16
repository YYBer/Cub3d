#include "cub3d_bonus.h"

void read_subject_file(char **argv, t_main *m)
{
   	m->filename = argv[1];
	m->total_chars_read = 0; 
    m->fd = open(m->filename, O_RDONLY);
    if (m->fd == -1)
    {
        printf("%s%s\"%s\"\n", ERR_MSG, ERR_FILE, m->filename);
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
    get_map_dims(m);
    fill_map(m);
    get_player_position(m);
	convert_map_data_c_to_i(m);	
	load_textures(m);
}

void get_player_position(t_main *m)
{
    int row;
    int col;
    bool found;
    char map_char;

    found = false;    
    row = 0;
    while(row < m->map.nrows)
    {
        col = 0;
        while(col < m->map.ncols)
        {
            map_char = m->map.data_c[row][col];
            if (map_char == 'N' || map_char == 'S' || map_char == 'W' || map_char == 'E')
            {
                if (found == true)
                {
                    printf("%s%s%s", ERR_MSG, ERR_FORMAT, ERR_DUP_PLAYPOS);
                    exit(EXIT_FAILURE);
                }
                // + 0.5 sets pos to middle of square
                m->pos.x = row + 0.5;
                m->pos.y = col + 0.5;
                found = true;
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
            col++;
        }
        row++;
    }
    if (found == false)
    {
        printf("%s%s%s", ERR_MSG, ERR_FORMAT, ERR_NO_PLAYPOS);
        exit(EXIT_FAILURE);
    }
}