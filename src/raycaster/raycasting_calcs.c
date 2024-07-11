#include "../../include/cub3d.h"

static void	ray_initial_data(int x, t_cube *cube)
{
	t_raycasting	*ray = &cube->grafic->raycasting;
	
	/* Calculate the initial data values */
	ray->cameraX = 2 * x / (double)WINDOW_WIDTH - 1;
	ray->rayDirX = cube->pj.dirX + cube->pj.planeX * ray->cameraX;
	ray->rayDirY = cube->pj.dirY + cube->pj.planeY * ray->cameraX;

	/* Player's map position */
	ray->mapX = (int) cube->pj.posX;
	ray->mapY = (int) cube->pj.posY;

	/* Get the X ray increment */
	if (ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);

	/* Get the Y ray increment */
	ray->deltaDistY = (ray->rayDirY == 0) ? 1e30 : fabs(1 / ray->rayDirY);
	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
}

static void	ray_rays_directions(t_cube *cube)
{
	t_raycasting *ray = &cube->grafic->raycasting;

	/* Check where the X ray is going to move */
	if (ray->rayDirX < 0) {
		ray->stepX = -1;
		ray->sideDistX = (cube->pj.posX - ray->mapX) * ray->deltaDistX;
	} else {
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - cube->pj.posX) * ray->deltaDistX;
	}

	/* Check where the Y ray is going to move */
	if (ray->rayDirY < 0) {
		ray->stepY = -1;
		ray->sideDistY = (cube->pj.posY - ray->mapY) * ray->deltaDistY;
	} else {
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - cube->pj.posY) * ray->deltaDistY;
	}
}

static void	ray_hits(t_cube *cube)
{
	int	hit;
	t_raycasting *ray = &cube->grafic->raycasting;

	hit = 0;

	/* Loop until the ray hit with a block different of a '0' ('1' or 'D')*/
	while (hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY) {
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		} else {
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (cube->map[ray->mapY][ray->mapX] != '0')
			hit = 1;
	}

	/* Check the distance between the player and the hit point */
	if (ray->side == 0)
		ray->perpWallDist = (ray->mapX - cube->pj.posX + (1 - ray->stepX) / 2) / ray->rayDirX;
	else
		ray->perpWallDist = (ray->mapY - cube->pj.posY + (1 - ray->stepY) / 2) / ray->rayDirY;

}

void	raycasting_calcs(int x, t_cube *cube)
{
	/* Initial rays and map data */
	ray_initial_data(x, cube);

	/* Calc rays directions and increments */
	ray_rays_directions(cube);

	/* Get the rays hits */
	ray_hits(cube);
}
