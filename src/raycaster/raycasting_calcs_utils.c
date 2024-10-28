/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calcs_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:59:47 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:59:49 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ray_rays_directions_x(t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->graphic->raycasting;
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->side_dist_x = (cube->pj.pos_x - ray->map_x) \
			* ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_dist_x = (ray->map_x + 1.0 - cube->pj.pos_x) \
			* ray->delta_dist_x;
	}
}

void	ray_rays_directions_y(t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->graphic->raycasting;
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->side_dist_y = (cube->pj.pos_y - ray->map_y) \
			* ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_dist_y = (ray->map_y + 1.0 - cube->pj.pos_y) \
			* ray->delta_dist_y;
	}
}
