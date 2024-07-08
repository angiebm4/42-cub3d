#include "../../include/cub3d.h"

int	line_is_empty(char *line, char *empty_set)
{
	int	index;

	index = 0;
	if (!line || !line[0])
		return (1);

	/* Iterate on the line */
	while (line[index])
	{
		/* If the currect character is not on the empty set, the line is not empty */
		if (ft_strchr(empty_set, line[index]) == NULL)
			return (0);
		index++;
	}

	return (1);
}

int	line_is_comment(char *line, char *comment_set)
{
	if (!line)
		return (0);

	/* Check if the first character is on the comment set */
	return (ft_strchr(comment_set, line[0]) != NULL);
}

int	line_is_placeholder(char *supposed_ph, t_parsed_data *parsed)
{
	char	**spl;
	int		index;
	int		res;

	/* Split the existing placeholders */
	spl = ft_split(VIEWS_PLACEHOLDERS, SEPARATOR_PLACEHOLDER);
	if (!spl)
		parse_error(ERROR_MALLOC, parsed, 0);

	/* Iterate on the placeholders */
	index = 0;
	res = -1;
	while (spl[index])
	{
		/* If the supposed_ch equals the current ph, the line is a placeholder */
		if (ft_strcmp(spl[index], supposed_ph) == 0)
		{
			res = index;
			break ;
		}
		index++;
	}
	ft_free_split(spl);
	return (res);
}

int	line_can_omitted(char *line)
{
	/* A line can be omitted if it is empty or if it is a comment*/
	return (
		line_is_comment(line, COMMENT_SET) || \
		line_is_empty(line, EMPTY_SET)
	);
}
