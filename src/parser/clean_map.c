#include "../../include/cub3d.h"

void	clean_map(char **map)
{
	size_t	size;

	size = map_length(map);
	while (size > 0)
	{
		size--;
		if (!line_is_empty(map[size], EMPTY_SET))
			break ;
		ft_mfree(1, &map[size]);
	}
}
