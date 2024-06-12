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
        /*TODO: check if pj can move*/
        
        cube->pj.unit_y -= MOVEMENT_PLAYER;
    }
    else if (keycode == A || keycode == LEFT)
    {
        /*TODO: check if pj can move*/
        cube->pj.unit_x -= MOVEMENT_PLAYER;
    }
    else if (keycode == S || keycode == DOWN)
    {
        /*TODO: check if pj can move*/
        cube->pj.unit_y += MOVEMENT_PLAYER;
    }
    else if (keycode == D || keycode == RIGHT)
    {
        /*TODO: check if pj can move*/
        cube->pj.unit_x += MOVEMENT_PLAYER;
    }
}

int key_hooks(int keycode, t_cube *cube)
{
    /* DEBUGGING: */
    mlx_clear_window(cube->grafic->mlx, cube->grafic->win);
    printf("tecla %d\n", keycode);
    if (keycode == ESC)
        end_program(cube);
    move_pj(keycode, cube);
    cube->pj.x = (int)(floor(cube->pj.unit_x)) / CUBE_HEIGTH;
    cube->pj.y = (int)(floor(cube->pj.unit_y)) / CUBE_HEIGTH;
    render(cube);
    printf("{%lf - %lf} <=> {%d - %d}\n", cube->pj.unit_x, cube->pj.unit_y, cube->pj.x, cube->pj.y);
    return(1);
}

void    hooking(t_cube *cube)
{
    mlx_hook(cube->grafic->win, ON_DESTROY, 0, &end_program, cube);
    mlx_key_hook(cube->grafic->win, key_hooks, cube);
}