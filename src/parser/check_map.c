#include "../../include/cub3d.h"

int	check_door(t_parsed_data *parsed)
{
	if (!search_map(parsed->map, 'D', NULL, NULL))
		return (0);
	return parsed->textures_name[DOOR_TEXTURE] == NULL;
}

void	check_map(t_parsed_data *parsed)
{
	int	count;

	count = 0;

	/* Check that aren't strange characters */
	count += map_check_characters(parsed->map, VALID_MAP_CHARS);

	/* Check the flood fill: 1 in case if errro; 0 otherwise */
	count += flood_fill(parsed->map);

	/* Check door texture if there is any door */
	count += check_door(parsed);

	/* DEBUGGING: print error count */
	// printf("=> {%d}\n", count);

	/* Check the reuslts of the map checkers */
	if (count != 0)
		parse_error(ERROR_MAP, parsed);
}
