#include "../include/cub3d.h"

void    clean_trash(t_cube *cube)
{
    /* TODO: eliminar parseo???'*/
    if (cube->grafic->mini_map->img)
        mlx_destroy_image(cube->grafic->mlx, cube->grafic->mini_map->img);
    if (cube->grafic->img)
        mlx_destroy_image(cube->grafic->mlx, cube->grafic->img);
    if (cube->grafic->win)
        mlx_destroy_window(cube->grafic->mlx, cube->grafic->win);
    if (cube->grafic)
        free(cube->grafic);
   if (cube->map)
        ft_free_split(cube->map);
    /* TODO: hay que elimirmar la mlx??*/
}