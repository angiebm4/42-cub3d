#include "../../include/cub3d.h"

static void	ray_initial_data(int x, t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->grafic->raycasting;
	ray->cameraX = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->rayDirX = cube->pj.dirX + cube->pj.planeX * ray->cameraX;
	ray->rayDirY = cube->pj.dirY + cube->pj.planeY * ray->cameraX;
	ray->mapX = (int) cube->pj.posX;
	ray->mapY = (int) cube->pj.posY;
	if (ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
}

static void	ray_rays_directions(t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->grafic->raycasting;
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (cube->pj.posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - cube->pj.posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (cube->pj.posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - cube->pj.posY) * ray->deltaDistY;
	}
}

static void	ray_hits(t_cube *cube)
{
	int				hit;
	t_raycasting	*ray;

	hit = 0;
	ray = &cube->grafic->raycasting;
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
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - cube->pj.posX + (1 - ray->stepX) / 2) / ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - cube->pj.posY + (1 - ray->stepY) / 2) / ray->rayDirY;
}

void	raycasting_calcs(int x, t_cube *cube)
{
	ray_initial_data(x, cube);
	ray_rays_directions(cube);
	ray_hits(cube);
}
