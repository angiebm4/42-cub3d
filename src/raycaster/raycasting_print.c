#include "../../include/cub3d.h"

void	raycasting_print_pixels(t_cube *cube)
{
	int	x;
	int	y;

	x = -1;
	while (++x < WINDOW_WIDTH)
	{
		y = -1;
		while (++y < WINDOW_HEIGTH / 2)
			ray_draw_pixel(x, y, pixel_conversor(&cube->grafic->default_pixels[CEILING_PIXEL]), cube);
		while (y < WINDOW_HEIGTH)
		{
			ray_draw_pixel(x, y, pixel_conversor(&cube->grafic->default_pixels[FLOOR_PIXEL]), cube);
			y++;
		}
	}
}

static void	ray_print_texture_loop(int x, t_cube *cube)
{
	int				y;
	t_raycasting	*ray;

	ray = &cube->grafic->raycasting;
	ray->step = 1.0 * TEXTURE_DIMENSION / ray->lineHeight;
	ray->texPos = (ray->startPoint - WINDOW_HEIGTH / 2 + ray->lineHeight / 2) * ray->step;
	y = ray->startPoint;
	while (y <= ray->endPoint)
	{
		ray->texY = (int) ray->texPos & (TEXTURE_DIMENSION - 1);
		ray->texPos += ray->step;
		ray->color = (int)*get_pixel(ray->texture, ray->texX, ray->texY);
		ray_draw_pixel(x, y, ray->color, cube);
		y++;
	}
}

void	ray_select_texture(t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->grafic->raycasting;
	if (ray->side == 0)
	{
		if (ray->rayDirX > 0)
			ray->texture = &cube->grafic->textures[WEST_TEXTURE];
		else
			ray->texture = &cube->grafic->textures[EAST_TEXTURE];
	}
	else
	{
		if (ray->rayDirY > 0)
			ray->texture = &cube->grafic->textures[NORTH_TEXTURE];
		else
			ray->texture = &cube->grafic->textures[SOUTH_TEXTURE];
	}
	if (cube->map[cube->grafic->raycasting.mapY][cube->grafic->raycasting.mapX] == 'D')
		ray->texture = &cube->grafic->textures[DOOR_TEXTURE];
}

void	ray_get_texture_pos(t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->grafic->raycasting;
	if (ray->side == 0)
		ray->wallX = cube->pj.posY + ray->perpWallDist * ray->rayDirY;
	else
		ray->wallX = cube->pj.posX + ray->perpWallDist * ray->rayDirX;
	ray->wallX -= floor(ray->wallX);
	ray->texX = (int)(ray->wallX * (double)TEXTURE_DIMENSION);
	if (ray->side == 0 && ray->rayDirX < 0)
		ray->texX = TEXTURE_DIMENSION - ray->texX - 1;
	if (ray->side == 1 && ray->rayDirY > 0)
		ray->texX = TEXTURE_DIMENSION - ray->texX - 1;
}

void	raycasting_print_textures(int x, t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->grafic->raycasting;
	ray->lineHeight = (int)(WINDOW_HEIGTH / ray->perpWallDist);
	ray->startPoint = -ray->lineHeight / 2 + WINDOW_HEIGTH / 2;
	if (ray->startPoint < 0)
		ray->startPoint = 0;
	ray->endPoint = ray->lineHeight / 2 + WINDOW_HEIGTH / 2;
	if (ray->endPoint >= WINDOW_HEIGTH)
		ray->endPoint = WINDOW_HEIGTH - 1;
	ray_get_texture_pos(cube);
	ray_select_texture(cube);
	ray_print_texture_loop(x, cube);
}
