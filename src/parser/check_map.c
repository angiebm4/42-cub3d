#include "../../include/cub3d.h"

static int	check_characters(char **map)
{
	size_t	i;
	size_t	j;

	i = -1;
	while (map[++i])
	{
		j = 0;
		while (map[i][++j])
		{
			if (!ft_strchr(VALID_MAP_CHARS, map[i][j]))
				return 0;
		}
	}
	return 1;
}


void	check_map(t_parsed_data *parsed)
{
	/* Check that aren't strange characters */
	check_characters(parsed->map);

	/* Check the flood fill */
	flood_fill(parsed->map);

	/* Check door texture if there is any door */
}
