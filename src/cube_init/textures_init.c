#include "../../include/cub3d.h"

void	textures_init(t_cube *cube, t_parsed_data *parsed)
{
	int	i;
	int	res;

	i = 0;
	while (i < TEXTURES_COUNT)
	{
		if (i == DOOR_TEXTURE && parsed->textures_name[i] == NULL)
		{
			i++;
			continue ;
		}
		res = load_image(parsed->textures_name[i], &cube->grafic->textures[i],
				cube->grafic, TEXTURE_DIMENSION);
		if (res)
		{
			ft_printf("%sINVALID TEXTURE%s\n", RED, CLEAR);
			destroy_parsed(parsed);
			end_program(cube);
		}
		i++;
	}
	i = -1;
	while (++i < PIXELS_COUNT)
		pixel_copy(&cube->grafic->default_pixels[i],
			&parsed->default_pixels[i]);
}
