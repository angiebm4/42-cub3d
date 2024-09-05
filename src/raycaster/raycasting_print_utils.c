#include "../../include/cub3d.h"

void	ray_draw_pixel(int x, int y, int color, t_cube *cube)
{
	char	*pixel;

	if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGTH)
	{
		pixel = get_pixel(&cube->grafic->screen, x, y);
		*(unsigned int *)pixel = color;
	}
}
