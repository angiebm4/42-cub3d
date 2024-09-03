#include "../../include/cub3d.h"

/* TODO: Get the texture pixel color instead of a default color */
static int	ray_select_color(t_cube *cube)
{
	int	color;
	
	color = 0xFFFF00;
	if (cube->grafic->raycasting.side)
		color /= 2;
	return (color);
}

static void	ray_draw_pixel(int x, int y, int color, t_cube *cube)
{
    char	*pixel;
	
	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGTH) {
        pixel = get_pixel(&cube->grafic->screen, x, y);
        *(unsigned int*)pixel = color;
    }
}

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

void	raycasting_print_textures(int x, t_cube *cube)
{
	int	lineHeight;
	int startPoint;
	int endPoint;
	int color;
	t_raycasting	*ray = &cube->grafic->raycasting;

	/* Calculate the height of the line */
	lineHeight = (int)(WINDOW_HEIGTH / ray->perpWallDist);

	/* Initial point of the line */
	startPoint = -lineHeight / 2 + WINDOW_HEIGTH / 2;
	if (startPoint < 0)
		startPoint = 0;

	/* End point of the printed line */
	endPoint = lineHeight / 2 + WINDOW_HEIGTH / 2;
	if (endPoint >= WINDOW_HEIGTH)
		endPoint = WINDOW_HEIGTH - 1;

	/* TODO: select the texture */
	color = ray_select_color(cube);

	/* Color the line on the image */
	for(int y = startPoint; y <= endPoint; y++)
		ray_draw_pixel(x, y, color, cube);
}
