#include "../../include/cub3d.h"

static void	move_fixed(int x, t_cube *cube)
{
	double	deltaX;
	double	angle;

	if (x != WINDOW_WIDTH/2)
	{
		deltaX = x - WINDOW_WIDTH/2;
		angle = deltaX * (MOUSE_ROTATION_SPEED);
		rotate_player(angle, &cube->pj);
	}
	mlx_mouse_move(cube->grafic->mlx, cube->grafic->win, WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
}

static void	move_not_fixed(int x, t_cube *cube)
{
	double	deltaX;
	double	angle;

	t_mouse *ray = &cube->grafic->mouse;
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
}

int mouse_move(int x, int y, t_cube *cube)
{
	(void)y;

	/* Check if the mouse should be fixed or not */
	if (cube->grafic->mouse.fixed)
		move_fixed(x, cube);
	else
		move_not_fixed(x, cube);

	return (0);
}
