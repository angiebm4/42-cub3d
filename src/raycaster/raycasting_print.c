#include "../../include/cub3d.h"

void	raycasting_print_pixels(t_cube *cube)
{
	int		x;
	int		y;
	t_pixel	*ceiling_pixel;
	t_pixel	*floor_pixel;

	x = -1;
	ceiling_pixel = &cube->graphic->default_pixels[CEILING_PIXEL];
	floor_pixel = &cube->graphic->default_pixels[FLOOR_PIXEL];
	while (++x < WINDOW_WIDTH)
	{
		y = -1;
		while (++y < WINDOW_HEIGTH / 2)
			ray_draw_pixel(x, y, pixel_conversor(ceiling_pixel), cube);
		while (y < WINDOW_HEIGTH)
		{
			ray_draw_pixel(x, y, pixel_conversor(floor_pixel), cube);
			y++;
		}
	}
}

static void	ray_print_texture_loop(int x, t_cube *cube)
{
	int				y;
	t_raycasting	*ray;

	ray = &cube->graphic->raycasting;
	ray->step = 1.0 * TEXTURE_DIMENSION / ray->line_height;
	ray->tex_pos = (ray->start_point - WINDOW_HEIGTH / 2 + ray->line_height / 2)
		* ray->step;
	y = ray->start_point;
	while (y <= ray->end_point)
	{
		ray->tex_y = (int) ray->tex_pos & (TEXTURE_DIMENSION - 1);
		ray->tex_pos += ray->step;
		ray->color = (int)*get_pixel(ray->texture, ray->tex_x, ray->tex_y);
		ray_draw_pixel(x, y, ray->color, cube);
		y++;
	}
}

void	ray_select_texture(t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->graphic->raycasting;
	if (ray->side == 0)
	{
		if (ray->raydir_x > 0)
			ray->texture = &cube->graphic->textures[WEST_TEXTURE];
		else
			ray->texture = &cube->graphic->textures[EAST_TEXTURE];
	}
	else
	{
		if (ray->raydir_y > 0)
			ray->texture = &cube->graphic->textures[NORTH_TEXTURE];
		else
			ray->texture = &cube->graphic->textures[SOUTH_TEXTURE];
	}
	if (cube->map[cube->graphic->raycasting.map_y]
		[cube->graphic->raycasting.map_x] == 'D')
		ray->texture = &cube->graphic->textures[DOOR_TEXTURE];
}

void	ray_get_texture_pos(t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->graphic->raycasting;
	if (ray->side == 0)
		ray->wall_x = cube->pj.pos_y + ray->perpWallDist * ray->raydir_y;
	else
		ray->wall_x = cube->pj.pos_x + ray->perpWallDist * ray->raydir_x;
	ray->wall_x -= floor(ray->wall_x);
	ray->tex_x = (int)(ray->wall_x * (double)TEXTURE_DIMENSION);
	if (ray->side == 0 && ray->raydir_x < 0)
		ray->tex_x = TEXTURE_DIMENSION - ray->tex_x - 1;
	if (ray->side == 1 && ray->raydir_y > 0)
		ray->tex_x = TEXTURE_DIMENSION - ray->tex_x - 1;
}

void	raycasting_print_textures(int x, t_cube *cube)
{
	t_raycasting	*ray;

	ray = &cube->graphic->raycasting;
	ray->line_height = (int)(WINDOW_HEIGTH / ray->perpWallDist);
	ray->start_point = -ray->line_height / 2 + WINDOW_HEIGTH / 2;
	if (ray->start_point < 0)
		ray->start_point = 0;
	ray->end_point = ray->line_height / 2 + WINDOW_HEIGTH / 2;
	if (ray->end_point >= WINDOW_HEIGTH)
		ray->end_point = WINDOW_HEIGTH - 1;
	ray_get_texture_pos(cube);
	ray_select_texture(cube);
	ray_print_texture_loop(x, cube);
}
