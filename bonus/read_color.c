#include "cub3d_bonus.h"

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
                printf("%s%s%s", ERR_MSG, ERR_FORMAT, ERR_COL_VAL);
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

uint32_t read_color_path(t_main *m)
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
		printf("%s%s%s", ERR_MSG, ERR_FORMAT, ERR_COL_VAL);
		close(m->fd);
		exit(EXIT_FAILURE);
	}
    return ((red << 24) | (green << 16) | (blue << 8) | 0xFF);
}

bool read_color_prefix(t_main *m, char *path)
{
	if (match_char(m, path[0]) == true)
	{
		bool *chosen_fileflag;

		read_char(m);
		while (m->char_read == ' ') // skip spaces
			read_char(m);
		chosen_fileflag = choose_fileflag(m, path);
		if (*chosen_fileflag == true)
		{
			printf("%s%s%s", ERR_MSG, ERR_FORMAT, ERR_DUPL);
			close(m->fd);
			exit(EXIT_FAILURE);
		}
		if (strcmp(path, "F") == 0)
		{
			m->floor_color = read_color_path(m);
			printf("fc:%i", m->floor_color);
		}
		if (strcmp(path, "C") == 0)
		{
			m->ceiling_color = read_color_path(m);
			printf("cc:%i", m->ceiling_color);
		}
		*chosen_fileflag = true;
		return (true);
	}
	return (false);
}