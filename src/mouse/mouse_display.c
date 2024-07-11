#include "../../include/cub3d.h"

void	mouse_display(t_cube *cube)
{
	if (cube->grafic->mouse.mouse_vision == 1)
	{
		cube->grafic->mouse.mouse_vision = 0;
		mlx_mouse_hide(cube->grafic->mlx, cube->grafic->win);
	}
	else
	{
		cube->grafic->mouse.mouse_vision = 1;
		mlx_mouse_show(cube->grafic->mlx, cube->grafic->win);
	}
}
