#include "../../include/cub3d.h"

char	**save_map(t_parsed_data *parsed, char *line)
{
	char	*buffer;
	char	*aux;
	char	**map;

	buffer = line;

	line = get_next_line(parsed->fd);
	while (line)
	{
		aux = ft_strjoin(buffer, line);
		free(buffer);
		buffer = aux;

		/* Iteration */
		free(line);
		line = get_next_line(parsed->fd);
	}

	/* TODO: malloc */
	map = ft_split(buffer, '\n');
	free(buffer);
	return map;
}
