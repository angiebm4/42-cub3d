#include "../../include/cub3d.h"

static void	move_fixed(int x, t_cube *cube)
{
	double	delta_x;
	double	angle;

	if (x != WINDOW_WIDTH / 2)
	{
		delta_x = x - WINDOW_WIDTH / 2;
		angle = delta_x * (MOUSE_ROTATION_SPEED);
		rotate_player(angle, &cube->pj);
	}
	mlx_mouse_move(cube->graphic->mlx, cube->graphic->win,
		WINDOW_WIDTH / 2, WINDOW_HEIGTH / 2);
}

static void	move_not_fixed(int x, t_cube *cube)
{
	double	delta_x;
	double	angle;
	t_mouse	*ray;

	ray = &cube->graphic->mouse;
	if (ray->lastX != -1)
	{
		delta_x = x - ray->lastX;
		if (delta_x != 0)
		{
			angle = delta_x * (MOUSE_ROTATION_SPEED);
			rotate_player(angle, &cube->pj);
		}
	}
	ray->lastX = x;
}

int	mouse_move(int x, int y, t_cube *cube)
{
	(void)y;
	if (cube->graphic->mouse.fixed)
		move_fixed(x, cube);
	else
		move_not_fixed(x, cube);
	return (0);
}
