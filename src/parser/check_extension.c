#include "../../include/cub3d.h"

int	check_extension(char *filename, char *extension)
{
	size_t	flnm_length;
	size_t	ext_length;

	/* Check the length of the filename */
	flnm_length = ft_strlen(filename);
	ext_length = ft_strlen(extension);
	if (flnm_length < ext_length)
		return (0);

	/* Otherwise, check the last size(extension) characters */
	return (ft_strcmp(extension, &filename[flnm_length - ext_length]) == 0);
}
