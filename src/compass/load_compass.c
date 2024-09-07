#include "../../include/cub3d.h"

int	load_compass(t_cube *cube)
{
	int	result;

	result = load_image(NORTH_COMPASS, &cube->grafic->compass[NORTH_TEXTURE], cube->grafic, COMPASS_SIZE);
	result += load_image(SOUTH_COMPASS, &cube->grafic->compass[SOUTH_TEXTURE], cube->grafic, COMPASS_SIZE);
	result += load_image(WEST_COMPASS, &cube->grafic->compass[WEST_TEXTURE], cube->grafic, COMPASS_SIZE);
	result += load_image(EAST_COMPASS, &cube->grafic->compass[EAST_TEXTURE], cube->grafic, COMPASS_SIZE);
	return (result != 0);
}
