/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:51:17 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 14:05:12 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	set_color(t_cube *cube, int mapX, int mapY)
{
	if (cube->map[mapY][mapX] == '0')
		return (H_GRASS_GREEN);
	if (cube->map[mapY][mapX] == '1')
		return (H_BROWN);
	if (cube->map[mapY][mapX] == 'D')
		return (H_GRAY);
	else
		return (H_RED);
}

void	errase_minimap(t_cube *cube)
{
	int	color;
	int	i;
	int	j;

	color = H_BLACK;
	i = 0;
	while (i < MINIMAP_HEIGHT)
	{
		j = 0;
		while (j < MINIMAP_WIDTH)
		{
			my_pixel_put(cube->graphic->mini_map, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_minimap(t_cube *cube, t_mapaux *mapaux)
{
	int	i;
	int	j;

	j = -1;
	while (++j < INCREMENT_VALUE_Y)
	{
		i = -1;
		while (++i < INCREMENT_VALUE_X)
		{
			if (floor(cube->pj.pos_x) == mapaux->map_x
				&& floor(cube->pj.pos_y) == mapaux->map_y)
			{
				my_pixel_put(cube->graphic->mini_map, mapaux->x + i, mapaux->y
					+ j, H_SKIN);
			}
			else
			{
				my_pixel_put(cube->graphic->mini_map, mapaux->x + i, mapaux->y
					+ j, set_color(cube, mapaux->map_x, mapaux->map_y));
			}
		}
	}
}

void	init_mapaux(t_cube *cube, t_mapaux *mapaux)
{
	mapaux->start_x = floor(cube->pj.pos_x) - MINIMAP_WIDTH / 2
		/ INCREMENT_VALUE_X;
	mapaux->start_y = floor(cube->pj.pos_y) - MINIMAP_HEIGHT / 2
		/ INCREMENT_VALUE_Y;
	mapaux->y = 0;
	mapaux->aux_y = 0;
	mapaux->x = 0;
	mapaux->aux_x = 0;
	mapaux->map_x = 0;
	mapaux->map_y = 0;
}

void	mini_map(t_cube *cube)
{
	t_mapaux	mapaux;

	errase_minimap(cube);
	init_mapaux(cube, &mapaux);
	while (mapaux.y < MINIMAP_HEIGHT)
	{
		mapaux.x = 0;
		mapaux.aux_x = 0;
		while (mapaux.x < MINIMAP_WIDTH)
		{
			mapaux.map_x = mapaux.start_x + mapaux.aux_x;
			mapaux.map_y = mapaux.start_y + mapaux.aux_y;
			if (mapaux.map_x >= 0 && mapaux.map_x < cube->map_w
				&& mapaux.map_y >= 0 && mapaux.map_y < cube->map_h)
				draw_minimap(cube, &mapaux);
			mapaux.x += INCREMENT_VALUE_X;
			mapaux.aux_x++;
		}
		mapaux.y += INCREMENT_VALUE_Y;
		mapaux.aux_y++;
	}
	mlx_put_image_to_window(cube->graphic->mlx, cube->graphic->win,
		cube->graphic->mini_map->img, 0, 0);
}
