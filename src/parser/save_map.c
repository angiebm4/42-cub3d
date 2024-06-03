#include "../../include/cub3d.h"

# define SUBSTITUTE_LINE	" \n"

static char	*add_line(char *line, char *buffer)
{
	char *aux;

	/* NOTE: this has to be checker :/ */
	if (line_is_empty(line, EMPTY_SET))
		line = SUBSTITUTE_LINE;
	
	/* If the line is a comment, we dont add it to the map */
	aux = buffer;
	if (!line_is_comment(line, COMMENT_SET))
	{
		/* TODO: strjoin malloc */
		aux = ft_strjoin(buffer, line);
		free(buffer);
	}
	return aux;
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
		buffer = add_line(line, buffer);

		/* Iteration */
		free(line);
		line = get_next_line(parsed->fd);
	}

	/* TODO: malloc */
	map = ft_split(buffer, '\n');
	free(buffer);
	return map;
}
