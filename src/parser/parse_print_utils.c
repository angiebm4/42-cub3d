#include "../../include/cub3d.h"

static char	*parse_color_ok(void)
{
	return (GREENFOSFI"  OK "CLEAR);
}

static char	*parse_color_ko(void)
{
	return (RED"ERROR"CLEAR);
}

char	*parse_check_texture(char *texture)
{
	if (texture)
		return (parse_color_ok());
	return (parse_color_ko());
}

void	parse_check_pixel(t_pixel *pixel, char **check)
{
	if (pixel_is_default(pixel))
		check[0] = parse_color_ko();
	else
		check[0] = parse_color_ok();
	if (pixel_is_valid(pixel))
		check[1] = parse_color_ok();
	else
		check[1] = parse_color_ko();
}
