#include "../../include/cub3d.h"

static void    save_pixel(t_parsed_data *parsed, char *buffer, int ph)
{
	char	**pixel_spl;
	int		index;

    /* TODO: check malloc error */
	index = ph - TEXTURES_COUNT;
    pixel_spl = ft_split(buffer, PIXEL_SEPARATOR);

    if (ft_matrix_length(pixel_spl) == 3)
    {
        parsed->default_pixels[index].red = ft_atoi(pixel_spl[0]);
		parsed->default_pixels[index].green = ft_atoi(pixel_spl[1]);
		parsed->default_pixels[index].blue = ft_atoi(pixel_spl[2]);
    }
    ft_free_split(pixel_spl);
}

int	save_placeholder(t_parsed_data *parsed, char **buffer, int ph)
{

	if (ph < 0 || ft_matrix_length(buffer) != 2)
		return 0;
	
	printf("==> {%d} [%s]\n", ph, buffer[0]);

	/* Check if the placeholder is a texture or a pixel */
	if (ph <  TEXTURES_COUNT)
		parsed->textures_name[ph] = ft_strdup(buffer[1]);
	else
		save_pixel(parsed, buffer[1], ph);

	return 1;
}
