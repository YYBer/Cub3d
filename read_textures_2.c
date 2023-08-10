#include "cub3d.h"

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