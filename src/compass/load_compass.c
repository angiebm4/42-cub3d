#include "../../include/cub3d.h"

int	load_compass_image(char *path, int index, t_mlx *graphic)
{
	return (load_image(path, &graphic->compass[index], graphic, COMPASS_SIZE));
}

int	load_compass(t_cube *cube)
{
	int		result;
	t_mlx	*graphic;

	graphic = cube->graphic;
	result = load_compass_image(NORTH_COMPASS1, NORTH_COMPASS_F1, graphic);
	result += load_compass_image(NORTH_COMPASS2, NORTH_COMPASS_F2, graphic);
	result += load_compass_image(SOUTH_COMPASS1, SOUTH_COMPASS_F1, graphic);
	result += load_compass_image(SOUTH_COMPASS2, SOUTH_COMPASS_F2, graphic);
	result += load_compass_image(WEST_COMPASS1, WEST_COMPASS_F1, graphic);
	result += load_compass_image(WEST_COMPASS2, WEST_COMPASS_F2, graphic);
	result += load_compass_image(EAST_COMPASS1, EAST_COMPASS_F1, graphic);
	result += load_compass_image(EAST_COMPASS2, EAST_COMPASS_F2, graphic);
	return (result != 0);
}
