# include "../../include/cub3d.h"

/*void	save_map(t_parsed_data *parsed, char *buffer)
{

}*/

int check_placeholder(t_parsed_data *parsed, char *buffer)
{
	char	**spl;
	int		placeholder;
	int		res;

	/* Split the line on the space charcater */
	spl = ft_split(buffer, ' ');

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
	char    *buffer;

	buffer = get_next_line(parsed->fd);
	while (buffer)
	{
		
		/* Check conditions to skip the line */
		if (
			!line_is_empty(buffer, EMPTY_SET) &&
			ft_strlen(buffer) != 1 &&
			!line_is_comment(buffer, COMMENT_SET)
		)
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
	while (buffer) {
		free(buffer);
		buffer = get_next_line(parsed->fd);
	}

	
}
