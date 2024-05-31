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
	char	*trimmed;

	/* Check if the placeholder is valid or not */
	if (ph < 0 || ft_matrix_length(buffer) != 2)
		return 0;
	
	/* TODO: check malloc error */
	trimmed = ft_strtrim(buffer[1], EMPTY_SET);

	/* Check if the placeholder is a texture or a pixel */
	if (ph <  TEXTURES_COUNT)
		parsed->textures_name[ph] = ft_strdup(trimmed);
	else
		save_pixel(parsed, trimmed, ph);
	
	/* Free the trimmed string memory */
	free(trimmed);

	return 1;
}
