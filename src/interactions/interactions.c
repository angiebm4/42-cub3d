#include "../../include/cub3d.h"

void	interactions_manage(int keycode, t_cube *cube)
{
	if (keycode == I)
		door_interaction(cube);
}
