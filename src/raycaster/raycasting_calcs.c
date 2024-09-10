#include "../../include/cub3d.h"

static void	ray_initial_data(int x, t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->grafic->raycasting;
	ray->cameraX = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->raydir_x = cube->pj.dir_x + cube->pj.plane_x * ray->cameraX;
	ray->raydir_y = cube->pj.dir_y + cube->pj.plane_y * ray->cameraX;
	ray->mapX = (int) cube->pj.pos_x;
	ray->mapY = (int) cube->pj.pos_y;
	if (ray->raydir_x == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->raydir_y);
	if (ray->raydir_y == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->raydir_y);
}

static void	ray_rays_directions(t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->grafic->raycasting;
	if (ray->raydir_x < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (cube->pj.pos_x - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - cube->pj.pos_x) * ray->deltaDistX;
	}
	if (ray->raydir_y < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (cube->pj.pos_y - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - cube->pj.pos_y) * ray->deltaDistY;
	}
}

static void	ray_hit_loop(t_raycasting *ray, t_cube *cube)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (cube->map[ray->mapY][ray->mapX] != '0')
			hit = 1;
	}
}

static void	ray_hits(t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->grafic->raycasting;
	ray_hit_loop(ray, cube);
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - cube->pj.pos_x + (1 - ray->stepX) / 2)
			/ ray->raydir_x;
	else
		ray->perpWallDist = (ray->mapY - cube->pj.pos_y + (1 - ray->stepY) / 2)
			/ ray->raydir_y;
}

void	raycasting_calcs(int x, t_cube *cube)
{
	ray_initial_data(x, cube);
	ray_rays_directions(cube);
	ray_hits(cube);
}
