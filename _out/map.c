#include "cub3d.h"

int	alloc_map(t_main *m)
{
	int	i;
	int	j;

	m->map = malloc(m->map_width * sizeof (int *));
	if (m->map == NULL)
		return (1);
	i = 0;
	while (i < m->map_width)
	{
		m->map[i] = malloc(m->map_height * sizeof(int));
		if (m->map[i] == NULL)
		{
			j = 0;
			while (j < i)
			{
				free(m->map[j]);
				j++;
			}
			free(m->map);
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_map(t_main *m)
{
	int	i;
	int	j;

	i = 0;
	while (i < m->map_width)
	{
		j = 0;
		while (j < m->map_height)
		{
			m->map[i][j] = wm[i][j];
			j++;
		}
		i++;
	}
}

void	free_map(t_main *m)
{
	int	i;

	i = 0;
	while (i < m->map_width)
	{
		free(m->map[i]);
		i++;
	}
	free(m->map);
}
