#include "../../include/cub3d.h"

void	mouse_display(t_cube *cube)
{
	if (cube->graphic->mouse.mouse_vision == 1)
	{
		cube->graphic->mouse.mouse_vision = 0;
		mlx_mouse_hide(cube->graphic->mlx, cube->graphic->win);
	}
	else
	{
		cube->graphic->mouse.mouse_vision = 1;
		mlx_mouse_show(cube->graphic->mlx, cube->graphic->win);
	}
}
