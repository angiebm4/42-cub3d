#include "../../include/cub3d.h"

int	check_extension(char *buffer, char *extension)
{
	size_t	bff_length;
	size_t	ext_length;

	bff_length = ft_strlen(buffer);
	ext_length = ft_strlen(extension);

	if (bff_length < ext_length)
		return 0;

	return ft_strcmp(extension, &buffer[bff_length - ext_length]) == 0;
}
