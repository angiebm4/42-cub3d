#include "../../include/cub3d.h"

int	check_door(t_parsed_data *parsed)
{
	/* Seach the door character on the map */
	if (!parsed->doors)
		return (0);

	/* If the door character was on the map, check if a texture has been saved */
	return (parsed->textures_name[DOOR_TEXTURE] == NULL);
}

int	check_player(char **map)
{
	int		i;
	int		j;
	size_t	count;

	/* Iterate the map */
	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			/* Check if the currect character is one of the player set */
			if (ft_strchr(PJ_CHARS, map[i][j]))
				count++;
			j++;
		}
		i++;
	}

	/* Return the number of player characters found on the map */
	return (count != 1);
}

void	check_map(t_parsed_data *parsed)
{
	int	count;

	count = 0;

	/* Check if a map has been saved on the file reading*/
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

	/* Check the results of the map checkers */
	if (count != 0)
		parse_error(ERROR_MAP, parsed, 1);
}
