#include "../../include/cub3d.h"

static void	check_texture(t_parsed_data *parsed)
{
	int	i;
	int	fd;
	int	result;

	/* Iterate on the textures, to check each one */
	i = -1;
	result = 0;
	while (++i < TEXTURES_COUNT)
	{
		/* If the door don't have text, continue (it's optional) */
		if (i == DOOR_TEXTURE && parsed->textures_name[i] == NULL)
			continue ;

		/* Check if the texture was on the config file  */
		if (!parsed->textures_name[i] && i != DOOR_TEXTURE)
		{
			result = 1;
			break ;
		}

		/* Check if the file exists. Better implementation: 'access' */
		fd = open(parsed->textures_name[i], O_RDONLY);
		if (fd < 0)
		{
			result = 1;
			break ;
		}
		ft_close(&fd);
	}

	/* Check the result flag */
	if (result)
		parse_error(ERROR_TEXTURES, parsed, 1);
}

static void	check_pixels(t_parsed_data *parsed)
{
	int	i;
	int	result;

	/* Iterate on each pixel */
	i = -1;
	result = 0;
	while (++i < PIXELS_COUNT)
	{
		/* Check if the currect pixel is valid */
		if (!pixel_is_valid(&parsed->default_pixels[i]))
		{
			result = 1;
			break ;
		}
	}

	/* Check the result flag */
	if (result)
		parse_error(ERROR_PIXELS, parsed, 1);
}

void	check_graphic(t_parsed_data *parsed)
{
	/* Check if the textures is okay (the door texture is managed by the map) */
	check_texture(parsed);

	/* Check if the pizels are valid */
	check_pixels(parsed);
}
