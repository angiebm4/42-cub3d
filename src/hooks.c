#include "../include/cub3d.h"

int end_program(t_cube *cube)
{
    if (cube->grafic->win)
        mlx_destroy_window(cube->grafic->mlx, cube->grafic->win);
    if (cube->map)
        ft_free_split(cube->map);
    exit(1);
}

void    move_pj(int keycode, t_cube *cube)
{
    if (keycode == W || keycode == UP)
    {
        /* TODO: check if pj can move */
        cube->pj->y -= 1;
        mini_map(cube);
    }
    else if (keycode == A || keycode == LEFT)
    {
        /* TODO: check if pj can move */
        cube->pj->x -= 1;
        mini_map(cube);
    }
    else if (keycode == S || keycode == DOWN)
    {
        /* TODO: check if pj can move */
        cube->pj->y += 1;
        mini_map(cube);
    }
    else if (keycode == D || keycode == RIGHT)
    {
        /* TODO: check if pj can move */
        cube->pj->x += 1;
        mini_map(cube);
    }
}

int key_hooks(int keycode, t_cube *cube)
{
    /* DEBUGGING: */
    printf("tecla %d\n", keycode);
    if (keycode == ESC)
        end_program(cube);
    move_pj(keycode, cube);
    return(1);
}

void    hooking(t_cube *cube)
{
    mlx_hook(cube->grafic->win, ON_DESTROY, 0, &end_program, cube);
    mlx_key_hook(cube->grafic->win, key_hooks, cube);
    /* DEBUGGING: */
    printf("uwu\n");
}