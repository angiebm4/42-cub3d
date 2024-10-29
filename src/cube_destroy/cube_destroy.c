/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_destroy.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lpastor- <lpastor-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:03:27 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/29 17:31:24 by lpastor-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	clean_images(t_image *images, size_t size, void *mlx)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (images[i].img)
			mlx_destroy_image(mlx, images[i].img);
		i++;
	}
}

static void	clean_minimap(t_cube *cube)
{
	if (cube->graphic->mlx && cube->graphic->mini_map)
		mlx_destroy_image(cube->graphic->mlx, cube->graphic->mini_map->img);
	if (cube->graphic->mini_map)
		free(cube->graphic->mini_map);
}

static void	screen_destroy(t_cube *cube)
{
	mlx_loop_end(cube->graphic->mlx);
	if (cube->graphic->screen.img)
	{
		mlx_destroy_image(cube->graphic->mlx, cube->graphic->screen.img);
		mlx_destroy_window(cube->graphic->mlx, cube->graphic->win);
	}
	clean_images(cube->graphic->textures, TEXTURES_COUNT, cube->graphic->mlx);
	clean_images(cube->graphic->compass, COMPASS_TEXTURES, cube->graphic->mlx);
	clean_minimap(cube);
	mlx_destroy_display(cube->graphic->mlx);
	free(cube->graphic->mlx);
	free(cube->graphic);
}

void	cube_destroy(t_cube *cube, int ret_value)
{
	if (cube->map)
		ft_free_split(cube->map);
	if (cube->doors)
		ft_lstclear(&cube->doors, free);
	if (cube->graphic->mlx)
		screen_destroy(cube);
	if (ret_value >= 0)
		exit(ret_value);
}
