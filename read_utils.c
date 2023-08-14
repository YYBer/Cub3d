#include "cub3d.h"

void	read_char(t_main *m)
{
    char	onechar[1];
	int		num_chars_read;

	num_chars_read = read(m->fd, &onechar, 1);
    if (num_chars_read < 1)
    {
        printf("%s%s", ERR_MSG, ERR_FILE);
		close(m->fd);
        exit(EXIT_FAILURE);
    }
	m->total_chars_read += num_chars_read;
	m->char_read = onechar[0];
}

bool match_char(t_main *m, char char_to_match)
{
	if (m->char_read == char_to_match)
    {
		return (true);
    }
	return (false);
}

void init_fileflags(t_main *m)
{
	m->fileflags.no = false;
	m->fileflags.so = false;
	m->fileflags.we = false;
	m->fileflags.ea = false;
	m->fileflags.f = false;
	m->fileflags.c = false;
}

bool *choose_fileflag(t_main *m, char *path)
{
	if (strcmp(path, "NO") == 0)
		return (&m->fileflags.no);
	if (strcmp(path, "SO") == 0)
		return (&m->fileflags.so);
	if (strcmp(path, "WE") == 0)
		return (&m->fileflags.we);
	if (strcmp(path, "EA") == 0)
		return (&m->fileflags.ea);
	if (strcmp(path, "F") == 0)
		return (&m->fileflags.f);
	if (strcmp(path, "C") == 0)
		return (&m->fileflags.c);				
	return (NULL);
}


void	read_prefixes(t_main *m)
{
	read_char(m);
	while (m->char_read == '\n') // skip newlines
		read_char(m);
	if (read_tex_prefix(m, "NO") == true)
		return;
	if (read_tex_prefix(m, "SO") == true)
		return;
	if (read_tex_prefix(m, "WE") == true)
		return;
	if (read_tex_prefix(m, "EA") == true)
		return;
	if (read_color_prefix(m, "F") == true)
		return;
	if (read_color_prefix(m, "C") == true)
		return;
	printf("%s%s%s", ERR_MSG, ERR_FORMAT, ERR_PREFIXES);
	close(m->fd);
	exit(EXIT_FAILURE);		
}

