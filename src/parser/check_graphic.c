#include "../../include/cub3d.h"

static void	check_texture(t_parsed_data *parsed)
{
	int	i;
	int	fd;
	int	result;

	i = -1;
	result = 0;
	while (++i < TEXTURES_COUNT)
	{
		if (i == DOOR_TEXTURE && parsed->textures_name[i] == NULL)
			continue ;
		if (!parsed->textures_name[i] && i != DOOR_TEXTURE)
		{
			result = 1;
			break ;
		}
		fd = open(parsed->textures_name[i], O_RDONLY);
		if (fd < 0)
		{
			result = 1;
			break ;
		}
		ft_close(&fd);
	}
	if (result)
		parse_error(ERROR_TEXTURES, parsed, 1);
}

static void	check_pixels(t_parsed_data *parsed)
{
	int	i;
	int	result;

	i = -1;
	result = 0;
	while (++i < PIXELS_COUNT)
	{
		if (!pixel_is_valid(&parsed->default_pixels[i]))
		{
			result = 1;
			break ;
		}
	}
	if (result)
		parse_error(ERROR_PIXELS, parsed, 1);
}

void	check_graphic(t_parsed_data *parsed)
{
	check_texture(parsed);
	check_pixels(parsed);
}
