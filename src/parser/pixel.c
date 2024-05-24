#include "../../include/cub3d.h"

void	reset_pixel(t_pixel *pixel)
{
	pixel->red = PIXEL_DEFAULT;
	pixel->green = PIXEL_DEFAULT;
	pixel->blue = PIXEL_DEFAULT;
}

int	pixel_is_valid(t_pixel *pixel)
{
	return (
		pixel->red < PIXEL_MIN || pixel->red > PIXEL_MAX ||
		pixel->green < PIXEL_MIN || pixel->green > PIXEL_MAX ||
		pixel->blue < PIXEL_MIN || pixel->blue > PIXEL_MAX
	);
}
