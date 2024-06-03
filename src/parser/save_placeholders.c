#include "../../include/cub3d.h"

void	save_texture(t_parsed_data *parsed, char *filename, int ph)
{
	if (check_extension(filename, TEXTURE_EXTENSION))
		parsed->textures_name[ph] = ft_strdup(filename);
}

static void	save_pixel(t_parsed_data *parsed, char *buffer, int ph)
{
	char	**pixel_spl;
	int		index;

    /* TODO: check malloc error */
	index = ph - TEXTURES_COUNT;
    pixel_spl = ft_split(buffer, PIXEL_SEPARATOR);

    if(map_length(pixel_spl) == 3)
    {
		if (ft_isnumber(pixel_spl[0]))
        	parsed->default_pixels[index].red = ft_atoi(pixel_spl[0]);
		if (ft_isnumber(pixel_spl[1]))
			parsed->default_pixels[index].green = ft_atoi(pixel_spl[1]);
		if (ft_isnumber(pixel_spl[2]))
			parsed->default_pixels[index].blue = ft_atoi(pixel_spl[2]);
    }
    ft_free_split(pixel_spl);
}

int	save_placeholder(t_parsed_data *parsed, char **buffer, int ph)
{
	/* Check if the placeholder is valid or not */
	if (ph < 0 || map_length(buffer) != 2)
		return 0;
	
	/* Check if the placeholder is a texture or a pixel */
	if (ph <  TEXTURES_COUNT)
		save_texture(parsed, buffer[1], ph);
	else
		save_pixel(parsed, buffer[1], ph);

	return 1;
}
