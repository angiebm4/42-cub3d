#include "../../include/cub3d.h"

int	load_compass(t_cube *cube)
{
	int	result;

	result =  load_image(NORTH_COMPASS1, &cube->grafic->compass[NORTH_COMPASS_F1], cube->grafic, COMPASS_SIZE);
	result += load_image(NORTH_COMPASS2, &cube->grafic->compass[NORTH_COMPASS_F2], cube->grafic, COMPASS_SIZE);

	result += load_image(SOUTH_COMPASS1, &cube->grafic->compass[SOUTH_COMPASS_F1], cube->grafic, COMPASS_SIZE);
	result += load_image(SOUTH_COMPASS2, &cube->grafic->compass[SOUTH_COMPASS_F2], cube->grafic, COMPASS_SIZE);

	result += load_image(WEST_COMPASS1, &cube->grafic->compass[WEST_COMPASS_F1], cube->grafic, COMPASS_SIZE);
	result += load_image(WEST_COMPASS2, &cube->grafic->compass[WEST_COMPASS_F2], cube->grafic, COMPASS_SIZE);

	result += load_image(EAST_COMPASS1, &cube->grafic->compass[EAST_COMPASS_F1], cube->grafic, COMPASS_SIZE);
	result += load_image(EAST_COMPASS2, &cube->grafic->compass[EAST_COMPASS_F2], cube->grafic, COMPASS_SIZE);
	return (result != 0);
}
