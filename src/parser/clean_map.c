#include "../../include/cub3d.h"

void	clean_map(char **map)
{
	size_t	size;

	size = map_length(map);

	/* Iterate in the map */
	while (size > 0)
	{
		size--;

		/* If the line is not empty, stop */
		if (!line_is_empty(map[size], EMPTY_SET))
			break ;
		
		/* Otherwise, clean the line */
		ft_mfree(1, &map[size]);
	}
}
