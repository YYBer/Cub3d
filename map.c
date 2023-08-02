#include "cub3d.h"

int	alloc_world_map(t_main *m)
{
	int	i;
	int	j;

	m->world_map = malloc(m->map_width * sizeof (int *));
	if (m->world_map == NULL)
		return (1);
	i = 0;
	while (i < m->map_width)
	{
		m->world_map[i] = malloc(m->map_height * sizeof(int));
		if (m->world_map[i] == NULL)
		{
			j = 0;
			while (j < i)
			{
				free(m->world_map[j]);
				j++;
			}
			free(m->world_map);
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_world_map(t_main *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->map_width)
	{
		j = 0;
		while (j < m->map_height)
		{
			m->world_map[i][j] = wm[i][j];
			j++;
		}
		i++;
	}
}

void	free_world_map(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->map_width)
	{
		free(m->world_map[i]);
		i++;
	}
	free(m->world_map);
}
