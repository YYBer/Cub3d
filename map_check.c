#include "cub3d.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little[0] == '\0')
		return ((char *)big);
	while (big[i] != '\0')
	{
		j = 0;
		while (big[i + j] == little[j] && ((i + j) < n))
		{
			if (big[i + j] == '\0' && little [j] == '\0')
				return ((char *)&big[i]);
			j++;
		}
		if (little[j] == '\0')
			return ((char *)big + i);
		i++;
	}
	return (0);
} //from libft

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
} //from libft

int	ft_check_map_command(int argc, char **argv)
{
    size_t i;

	if(argc != 2)
	{
		printf("wrong number of args\n");
		return (1);
	}
	i = ft_strlen((const char *)argv[1]);
	if (ft_strnstr(&argv[1][i - 4], ".cub", 4) == NULL)
	{
		printf("file type is wrong, should be .cub"); //todo
		return (1);
	}
	return (0);
}
