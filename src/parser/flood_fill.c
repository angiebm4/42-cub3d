#include "../../include/cub3d.h"

static char	**copy_matrix(char **matrix)
{
	char **cpy;
	int	index;

	index = 0;
	if (!matrix)
		return NULL;
	cpy = malloc((ft_matrix_length(matrix) + 1) * sizeof(char *));
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

static int	search_matrix(char **matrix, char ch, int *x, int *y)
{
	int	i;
	int	j;

	i = -1;
	if (!matrix || !x || !y)
		return (0);
	while (matrix[++i])
	{
		j = -1;
		while (matrix[i][++j])
		{
			if (matrix[i][j] == ch)
			{
				*y = i;
				*x = j;
				return (1);
			}
		}
	}
	return (0);
}

static int	is_invalid_position(int x, int y, char **map)
{
	/* Check if the coordenates are out of the map */
	size_t	st_y;

	st_y = y;
	if (x < 0 || y < 0 || st_y >= (ft_matrix_length(map)) || x >= ft_strlen(map[y]))
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

int	flood_fill(char **map)
{
	char	**cpy;
	int		x;
	int		y;
	int		result;

	/* TODO: check mallco error */
	cpy = copy_matrix(map);

	result = 0;
	while (!result && search_matrix(cpy, '0', &x, &y))
		result = rec_floof_fill(x, y, cpy);

	int index = -1;
	while (cpy[++index])
		printf("=> [%s]\n", cpy[index]);
	printf("\t## {%d} ##\n", result);

	ft_free_split(cpy);
	return result;
}