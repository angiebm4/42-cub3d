#include "../../include/cub3d.h"

int	map_check_characters(char **map, char *set)
{
	size_t	i;
	size_t	j;

	/* Iterate on the map */
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			/* If the character is not part of the possible characters set, error */
			if (!ft_strchr(set, map[i][j]))
				return (1);
		}
	}
	return (0);
}

char	**copy_map(char **matrix)
{
	char	**cpy;
	int		index;

	index = 0;
	if (!matrix)
		return (NULL);
	cpy = malloc((map_length(matrix) + 1) * sizeof(char *));
	if (!cpy)
		return (NULL);
	while (matrix[index])
	{
		cpy[index] = ft_strdup(matrix[index]);
		if (!cpy[index])
		{
			while (--index >= 0)
				free(cpy[index]);
			free(cpy);
			return (NULL);
		}
		index++;
	}
	cpy[index] = NULL;
	return (cpy);
}

int	search_map(char **map, char ch, int *x, int *y)
{
	int	i;
	int	j;

	i = -1;
	if (!map)
		return (0);

	/* Iterate on the map */
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			/* If the curernt character is the searched character, save the coordenates */
			if (map[i][j] == ch)
			{
				if (y)
					*y = i;
				if (x)
					*x = j;
				return (1);
			}
		}
	}
	return (0);
}

size_t	map_length(char **matrix)
{
	size_t	index;

	index = 0;
	while (matrix[index])
		index++;
	return (index);
}
