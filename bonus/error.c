#include "cub3d_bonus.h"

void	ft_error(char *str, t_main *m)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	write(2, str, i);
	write(2, "\n", 1);
	if (m)
	{
		if (m->texture_alloc == true)
			delete_textures(m);
		if (m->map.data_alloc == true)
			free_map_data(&m->map);
	}
}