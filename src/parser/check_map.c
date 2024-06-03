#include "../../include/cub3d.h"


void	check_map(t_parsed_data *parsed)
{
	/* Check that aren't strange characters */
	map_check_characters(parsed->map, VALID_MAP_CHARS);

	/* Check the flood fill: 1 in case if errro; 0 otherwise */
	flood_fill(parsed->map);

	/* Check door texture if there is any door */
}
