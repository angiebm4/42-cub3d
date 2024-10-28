/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_trash.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:03:09 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:03:20 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    clean_trash(t_cube *cube)
{
    /* TODO: eliminar parseo???*/
    /* TODO: eliminar texturas ??*/
    if (cube->graphic->mini_map->img)
        mlx_destroy_image(cube->graphic->mlx, cube->graphic->mini_map->img);
//     if (cube->graphic->img)
//         mlx_destroy_image(cube->graphic->mlx, cube->graphic->img);
//     if (cube->graphic->win)
//         mlx_destroy_window(cube->graphic->mlx, cube->graphic->win);
//     if (cube->graphic)
//         free(cube->graphic);
//    if (cube->map)
//         ft_free_split(cube->map);
    /* TODO: hay que elimirmar la mlx??*/
}