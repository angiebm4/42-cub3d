/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_calcs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:59:52 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 14:09:22 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static void	ray_initial_data(int x, t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->graphic->raycasting;
	ray->camera_x = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->raydir_x = cube->pj.dir_x + cube->pj.plane_x * ray->camera_x;
	ray->raydir_y = cube->pj.dir_y + cube->pj.plane_y * ray->camera_x;
	ray->map_x = (int) cube->pj.pos_x;
	ray->map_y = (int) cube->pj.pos_y;
	if (ray->raydir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->raydir_y);
	if (ray->raydir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->raydir_y);
}

static void	ray_rays_directions(t_cube *cube)
{
	ray_rays_directions_x(cube);
	ray_rays_directions_y(cube);
}

static void	ray_hit_loop(t_raycasting *ray, t_cube *cube)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->side_dist_x < ray->side_dist_y)
		{
			ray->side_dist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_dist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (cube->map[ray->map_y][ray->map_x] != '0')
			hit = 1;
	}
}

static void	ray_hits(t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->graphic->raycasting;
	ray_hit_loop(ray, cube);
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - cube->pj.pos_x + \
			(1 - ray->step_x) / 2) / ray->raydir_x;
	else
		ray->perp_wall_dist = (ray->map_y - cube->pj.pos_y + \
			(1 - ray->step_y) / 2) / ray->raydir_y;
}

void	raycasting_calcs(int x, t_cube *cube)
{
	ray_initial_data(x, cube);
	ray_rays_directions(cube);
	ray_hits(cube);
}
