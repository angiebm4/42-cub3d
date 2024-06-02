# include "../../include/cub3d.h"

static void	check_map(t_parsed_data *parsed, char *buffer)
{
	/* If there is no line, the file dont have a map */
	if (!buffer)
		return ;

	/* Otherwise, the rest of the map is the rest of the file */
	parsed->map = save_map(parsed, buffer);

	/* DEBUGGING: printing and deleting the map */
	// int index = -1;
	// while (parsed->map && parsed->map[++index])
	// 	printf("{%d} [%s]\n", index, parsed->map[index]);
	// ft_free_split(parsed->map);
}

static int check_placeholder(t_parsed_data *parsed, char *buffer)
{
	char	**spl;
	int		placeholder;
	int		res;
	char	*trimmed;

	/* Delete the usefull characters on the left and right side */
	/* TODO: malloc */
	trimmed = ft_strtrim(buffer, EMPTY_SET);

	/* Split the line on the space charcater */
	/* TODO: malloc */
	spl = ft_split(trimmed, ' ');
	free(trimmed);

	/* Check if there is a placeholder on the line */
	placeholder = line_is_placeholder(spl[0]);

	/* If the line is a placeholder, the information will be saved */
	res = save_placeholder(parsed, spl, placeholder);

	/* Free the splitted string created before */
	ft_free_split(spl);
	
	/* Otherwise, save the placeholder data */
	return res;
}

void    parse_file(t_parsed_data *parsed)
{
	char	*buffer;

	buffer = get_next_line(parsed->fd);
	while (buffer)
	{	
		/* Check conditions to skip the line */
		if (!line_can_omitted(buffer))
		{
			/* If the line is not a placeholder, exit the loop */
			if (!check_placeholder(parsed, buffer))
				break ;
		}

		/* Iterate on the map*/
		free(buffer);
		buffer = get_next_line(parsed->fd);
	}

	/* At this point, the next lines should be the map data */
	check_map(parsed, buffer);
}
