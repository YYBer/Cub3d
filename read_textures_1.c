#include "cub3d.h"

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