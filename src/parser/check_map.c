#include "../../include/cub3d.h"

int	check_door(t_parsed_data *parsed)
{
	if (!search_map(parsed->map, 'D', NULL, NULL))
		return (0);
	return parsed->textures_name[DOOR_TEXTURE] == NULL;
}

int	check_player(char **map)
{
	int	i;
	int	j;
	size_t	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(PJ_CHARS, map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	return (count != 1);
}

void	check_map(t_parsed_data *parsed)
{
	int	count;

	count = 0;
	if (!parsed->map)
		parse_error(ERROR_MAP, parsed, 1);

	/* Check that aren't strange characters */
	count += map_check_characters(parsed->map, VALID_MAP_CHARS);

	/* Check that the number of players is just 1 */
	count += check_player(parsed->map);

	/* Check the flood fill: 1 in case if errro; 0 otherwise */
	count += flood_fill(parsed->map, parsed);

	/* Check door texture if there is any door */
	count += check_door(parsed);

	/* DEBUGGING: print error count */
	// printf("=> {%d}\n", count);

	/* Check the reuslts of the map checkers */
	if (count != 0)
		parse_error(ERROR_MAP, parsed, 1);
}
