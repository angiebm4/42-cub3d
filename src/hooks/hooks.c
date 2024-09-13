#include "../include/cub3d.h"

int	end_program(t_cube *cube)
{
	cube_destroy(cube, 0);
	return (0);
}

int	key_hooks(int keycode, t_cube *cube)
{
	if (keycode == ESC)
		end_program(cube);
	mouse_controller(keycode, cube);
	moves(keycode, cube);
	interactions_manage(keycode, cube);
	return (0);
}

void	hooking(t_cube *cube)
{
	mlx_hook(cube->graphic->win, ON_KEYDOWN, 1L << 0, key_hooks, cube);
	mlx_hook(cube->graphic->win, ON_DESTROY, 0, end_program, cube);
	mlx_hook(cube->graphic->win, ON_MOUSEMOVE, 1L << 6, mouse_move, cube);
	mlx_loop_hook(cube->graphic->mlx, render, cube);
}
