// cc -Wall -Werror -Wextra read_any_order.c && ./a.out

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>

// TODO: fix ERROR: cannot parse map file(read_prefixes) - we are one char too far ahead
// DONE: Except for the map, each type of information from an element can be separated by one or more space(s). [???]

typedef struct s_fileflags {
	bool no;
	bool so;
	bool we;
	bool ea;
	bool f;
	bool c;
}	t_fileflags;

typedef struct s_main {
	char 		*filename;
	int			fd;
	char		char_read;
	int			total_chars_read;
	char		*tex_paths[4];
	int			ceiling_color;
	int			floor_color;
	t_fileflags fileflags;
}	t_main;

void	read_char(t_main *m)
{
    char	onechar[1];
	int		num_chars_read;

	num_chars_read = read(m->fd, &onechar, 1);
    if (num_chars_read < 1)
    {
        printf("file error\n");
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

int read_color_value(t_main *m)
{    
    char    color_str[PATH_MAX]; 
    int     i;
    bool    non_digit_found;

    non_digit_found = false;
    i = 0;
    while(non_digit_found == false)
    {
        if (m->char_read < '0' || m->char_read > '9') // if non-digit found
        {
            if (i == 0) // if no digits have been read previously and we find a non-digit map format is invalid
            {
                printf("invalid map format(color)\n");
				close(m->fd);
                exit(EXIT_FAILURE);
            }                        
            else // if digits been read previously and we find a non-digit, set flag and continue
            {
                non_digit_found = true;
            }
        }
        else // if digit found
        {
            color_str[i] = m->char_read;
            i++;
			read_char(m);
        }
    }
    color_str[i] = '\0';
    return (atoi(color_str)); // convert to ft_atoi!
}

int read_color_path(t_main *m)
{
    int     red;
    int     green;
    int     blue;

    red = read_color_value(m);
	read_char(m);
	match_char(m, ',');
	while (m->char_read == ' ') // skip spaces
		read_char(m);
    green = read_color_value(m);
	read_char(m);
	match_char(m, ',');
	while (m->char_read == ' ') // skip spaces
		read_char(m);	
    blue = read_color_value(m);
	if (red < 0 || red > 255 || green < 0 || green > 255 || blue < 0 || blue > 255)
	{
		printf("ERROR: invalid color value\n");
		close(m->fd);
		exit(EXIT_FAILURE);
	}
    return ((red << 24) | (green << 16) | (blue << 8) | 0xFF);
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

void print_rgba(int value)
{
    // if (value < 0 || value > 0xFFFFFFFF) {
    //     printf("Input value must be between 0 and 4294967295 (0xFFFFFFFF)\n");
    //     return;
    // }

    int red = (value >> 24) & 0xFF;
    int green = (value >> 16) & 0xFF;
    int blue = (value >> 8) & 0xFF;
    int alpha = value & 0xFF;

    printf("0x%02X%02X%02X%02X\n", red, green, blue, alpha);
}


bool read_color_prefix(t_main *m, char *path)
{
	if (match_char(m, path[0]) == true)
	{
		bool *chosen_fileflag;
		// printf("%c found\n", path[0]);
		read_char(m);
		while (m->char_read == ' ') // skip spaces
			read_char(m);
		chosen_fileflag = choose_fileflag(m, path);
		if (*chosen_fileflag == true)
		{
			printf("ERROR: multiple %s paths in file(2)\n", path);
			close(m->fd);
			exit(EXIT_FAILURE);
		}
		printf("%s path found:", path);
		if (strcmp(path, "F") == 0)
		{
			m->floor_color = read_color_path(m);
			print_rgba(m->floor_color);	
		}
		if (strcmp(path, "C") == 0)
		{
			m->ceiling_color = read_color_path(m);
			print_rgba(m->ceiling_color);	
		}
		*chosen_fileflag = true;
		return (true);
	}
	return (false);
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
	printf("ERROR: cannot parse map file(read_prefixes)\n");
	close(m->fd);
	exit(EXIT_FAILURE);		
}

int main()
{
	t_main m;
	
	m.filename = "subject_map_test_map1.cub";
	m.fd = open(m.filename, O_RDONLY);
	init_fileflags(&m);
	read_prefixes(&m);
	read_prefixes(&m);	
	read_prefixes(&m);
	read_prefixes(&m);
	read_prefixes(&m);
	read_prefixes(&m);
	close(m.fd);
}