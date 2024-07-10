#include "../../include/cub3d.h"

int mouse_move(int x, int y, t_cube *cube)
{
	(void)y;
	double	deltaX;
	double	angle;
	t_raycasting *ray = &cube->grafic->raycasting;

	// mlx_mouse_move(cube->grafic->mlx, cube->grafic->win, WINDOW_WIDTH/2, WINDOW_HEIGTH/2);
	if (ray->lastX != -1)
	{
		deltaX = x - ray->lastX;
		if (deltaX != 0)
		{
			angle = deltaX * (MOUSE_ROTATION_SPEED);
			rotate_player(angle, &cube->pj);
		}
	}
	
	ray->lastX = x;
	return 0;
}
