#include "../../include/cub3d.h"

static int	is_invalid_position(int x, int y, char **map)
{
	/* Check if the coordenates are out of the map */
	size_t	st_y;

	st_y = y;
	if (x < 0 || y < 0 || st_y >= (map_length(map)) || x >= ft_strlen(map[y]))
		return (1);

	/* Check if the corrdenate is out of the line */
	if (ft_strlen(map[y]) <= x)
		return (1);

	/* Check if the position is an space */
	if (map[y][x] == ' ')
		return (1);
	
	/* Added here more comprobations if it is neccesary... */

	return (0);
}

int	rec_floof_fill(int x, int y, char **map)
{
	int	count;
	/* Error case:
		-> Se sale del mapa
		-> ch == space
		[X] No es una posicion valida (y = 20 donde strlen() == 3)	
	*/

	/* Check if the position is valid */
	if (is_invalid_position(x, y, map))
		return (1);

	/* Default exit case */
	if (map[y][x] == '1')
		return (0);
	map[y][x] = '1';

	/* Recursive call */
	count = 0;
	count += rec_floof_fill(x, y - 1, map);
	count += rec_floof_fill(x + 1, y, map);
	count += rec_floof_fill(x, y + 1, map);
	count += rec_floof_fill(x - 1, y, map);

	/* Return state result */
	return (count != 0);
}

int	flood_fill(char **map, t_parsed_data *parsed)
{
	char	**cpy;
	int		x;
	int		y;
	int		result;

	cpy = copy_map(map);
	if (!cpy)
		parse_error(ERROR_MALLOC, parsed, 0);

	result = 0;
	while (!result && search_map(cpy, '0', &x, &y))
		result = rec_floof_fill(x, y, cpy);

	/* DEBUGGING: print cpy map */
	// int index = -1;
	// while (cpy[++index])
	// 	printf("=> [%s]\n", cpy[index]);
	ft_free_split(cpy);

	/* Return the final state of the filling action */
	return result;
}