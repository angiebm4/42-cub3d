#include "../include/cub3d.h"

int end_program(t_cube *cube)
{
    if (cube->grafic->win)
        mlx_destroy_window(cube->grafic->mlx, cube->grafic->win);
    if (cube->map)
        ft_free_split(cube->map);
    exit(0);
}

int key_hooks(int keycode, t_cube *cube)
{
    /* DEBUGGING: */
    render(cube);
    if (keycode == ESC)
        end_program(cube);
    return(1);
}

void    hooking(t_cube *cube)
{
    mlx_hook(cube->grafic->win, ON_DESTROY, 0, &end_program, cube);
    mlx_key_hook(cube->grafic->win, key_hooks, cube);
}