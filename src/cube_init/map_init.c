#include "../../include/cub3d.h"

void	map_init(t_cube *cube, t_parsed_data *parsed)
{
	int	i;

	i = 0;
	cube->map = malloc(sizeof(char *) * (map_length(parsed->map) + 1));
	if (cube->map == NULL)
		cube_destroy(cube, 1);
	while (parsed->map[i])
	{
		cube->map[i] = ft_strdup(parsed->map[i]);
		if (cube->map[i] == NULL)
			cube_destroy(cube, 1);
		i++;
	}
	cube->map[i] = NULL;
}
