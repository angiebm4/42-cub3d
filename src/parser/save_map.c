#include "../../include/cub3d.h"

#define SUBSTITUTE_LINE	" \n"

static char	*add_line(char *line, char *buffer, t_parsed_data *parsed)
{
	char	*aux;

	/* NOTE: this has to be check with maps :/ */
	if (line_is_empty(line, EMPTY_SET))
		line = SUBSTITUTE_LINE;

	/* If the line is a comment, we dont add it to the map */
	aux = buffer;
	if (!line_is_comment(line, COMMENT_SET))
	{
		aux = ft_strjoin(buffer, line);
		if (!aux)
			parse_error(ERROR_MALLOC, parsed, 0);
		free(buffer);
	}
	return (aux);
}

char	**save_map(t_parsed_data *parsed, char *line)
{
	char	*buffer;
	char	**map;

	buffer = line;

	line = get_next_line(parsed->fd);
	while (line)
	{
		/* Function to add the line to the buffer, returning the new buffer */
		buffer = add_line(line, buffer, parsed);

		/* Iteration */
		free(line);
		line = get_next_line(parsed->fd);
	}

	/* Divide the buffer by the '\n' character, so the map can be saved on a matrix */
	map = ft_split(buffer, '\n');
	if (!map)
		parse_error(ERROR_MALLOC, parsed, 0);
	free(buffer);
	return (map);
}
