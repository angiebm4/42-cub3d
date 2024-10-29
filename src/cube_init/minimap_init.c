/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:04:27 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/29 10:42:49 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	get_map_measures(t_cube *cube)
{
	int	w;
	int	h;

	h = 0;
	while (cube->map[h])
	{
		w = 0;
		while (cube->map[h][w])
		{
			if (w > cube->map_w)
				cube->map_w = w;
			w++;
		}
		if (h > cube->map_h)
			cube->map_h = h;
		h++;
	}
	cube->map_h += 1;
	cube->map_w += 1;
}

static void	create_image_map(t_cube *cube)
{
	cube->graphic->mini_map->img = mlx_new_image(cube->graphic->mlx,
			MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (cube->graphic->mini_map->img == NULL)
		exit(1);
	cube->graphic->mini_map->data_addr = mlx_get_data_addr(
			cube->graphic->mini_map->img,
			&cube->graphic->mini_map->bpp, &cube->graphic->mini_map->size_line,
			&cube->graphic->mini_map->endian);
}

void	minimap_init(t_cube *cube)
{
	cube->graphic->mini_map = ft_calloc(1, sizeof(t_image));
	if (!cube->graphic->mini_map)
		cube_destroy(cube, 1);
	create_image_map(cube);
	get_map_measures(cube);
}
