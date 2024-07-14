#include "../../include/cub3d.h"

static void	door_change(t_cube *cube)
{
	int	x_player;
	int	y_player;

	x_player = (int)cube->pj.posX;
	y_player = (int)cube->pj.posY;

	/* TODO: */
}

void	interactions(int keycode, t_cube *cube)
{
	if (keycode == I)
		door_change(cube);
}
