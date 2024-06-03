#include "../../include/cub3d.h"

static int	check_characters(char **map, char *set)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][++j])
		{
			if (!ft_strchr(set, map[i][j]))
				return 1;
		}
	}
	return 0;
}


void	check_map(t_parsed_data *parsed)
{
	/* Check that aren't strange characters */
	check_characters(parsed->map, VALID_MAP_CHARS);

	/* Check the flood fill: 1 in case if errro; 0 otherwise */
	flood_fill(parsed->map);

	/* Check door texture if there is any door */
}
