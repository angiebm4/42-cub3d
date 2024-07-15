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
    // printf("==> %d\n", keycode);
    if (keycode == ESC)
        end_program(cube);
    mouse_controller(keycode, cube);
    moves(keycode, cube);
    interactions_manage(keycode, cube);
    return(0);
}

void    hooking(t_cube *cube)
{
    /* Key press */
    mlx_hook(cube->grafic->win, ON_KEYDOWN, 1L<<0, key_hooks, cube);
    
    /* Window X button */
    mlx_hook(cube->grafic->win, ON_DESTROY, 0, end_program, cube);

    /* Mouse movement */
    mlx_hook(cube->grafic->win, ON_MOUSEMOVE, 1L<<6, mouse_move, cube);

    /* Loop hook */
    mlx_loop_hook(cube->grafic->mlx, render, cube);
}