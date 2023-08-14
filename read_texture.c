#include "cub3d.h"

char *read_wall_tex_path(t_main *m)
{
    char   path_str[PATH_MAX];
    int     i;

    i = 0;
    while(1)
    {
        if (m->char_read == '\n')
            break;
        path_str[i] = m->char_read;
        i++;
		read_char(m);
    }
    path_str[i] = '\0';
	return(strdup(path_str));
}

int choose_tex_path_index(char *path)
{
	if (strcmp(path, "NO") == 0)
		return (0);
	if (strcmp(path, "SO") == 0)
		return (1);
	if (strcmp(path, "WE") == 0)
		return (2);
	if (strcmp(path, "EA") == 0)
		return (3);		
	return (-1);
}

bool read_tex_prefix(t_main *m, char *path)
{
	if (match_char(m, path[0]) == true)
	{
		// printf("%c found\n", path[0]);
		read_char(m);
		if (match_char(m, path[1]) == true)
		{
			bool *chosen_fileflag;
			int tex_path_index;
			// printf("%c found\n", path[1]);
			read_char(m);
			while (m->char_read == ' ') // skip spaces
				read_char(m);
			chosen_fileflag = choose_fileflag(m, path);
			if (*chosen_fileflag == true)
			{
				printf("ERROR: multiple %s paths in file\n", path);
				close(m->fd);
				exit(EXIT_FAILURE);
			}
			printf("%s path found:", path);
			tex_path_index = choose_tex_path_index(path);
			m->tex_paths[tex_path_index] = read_wall_tex_path(m);
			printf("%s\n", m->tex_paths[tex_path_index]);
			*chosen_fileflag = true;
			return (true);
		}
		else
		{	
			printf("ERROR: cannot parse map file\n");
			close(m->fd);
			exit(EXIT_FAILURE);
		}
	}
	return (false);
}