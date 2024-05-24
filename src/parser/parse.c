#include "../../include/cub3d.h"

static void	parse_errors(int error)
{
	printf("[ Error ] ");
	if (error == ERROR_INVALID_ARGS)
		printf("Invalid number of arguments!\n");
	else
		printf("Success(\\\\(·o·;)\n");
	exit(1);
}

static void	init_parser_data(t_parsed_data *parsed)
{
	size_t	index;
	
	/* Init the main fd */
	parsed->fd = -1;

	/* Init the strings and the fds */
	index = -1;
	ft_bzero(parsed, sizeof(*parsed));
	while (++index < TEXTURES_COUNT)
		parsed->textures_fds[index] = -1;
	
	/* Init the pixels */
	reset_pixel(&parsed->floor);
	reset_pixel(&parsed->ceiling);
}

/*#########################################################*/

void	parse(int argc, char **argv, t_parsed_data *parsed)
{
	(void) argv, (void)parsed;
	if (argc != 2)
		parse_errors(ERROR_INVALID_ARGS);

	init_parser_data(parsed);
	/* TODO: Rest of parse */
}

void	parse_print(int output, t_parsed_data parsed)
{
	/* TODO: msg to report the parser */
}

void	destroy_parsed(t_parsed_data *parsed)
{
	size_t	index;
	
	/* Close the config file fd */
	ft_close(&(parsed->fd));

	index = -1;
	while (++index < TEXTURES_COUNT)
	{
		/* Delete the files names and their fds */
		if (parsed->textures_name[index])
		{
			free(parsed->textures_name[index]);
			parsed->textures_name[index] = NULL;
		}
		ft_close(&(parsed->textures_fds[index]));
	}

	/* Reset the pixels */
	reset_pixel(&parsed->floor);
	reset_pixel(&parsed->ceiling);
}
