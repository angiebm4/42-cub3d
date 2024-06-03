#include "../../include/cub3d.h"

void	parse_error(int error, t_parsed_data *parsed)
{
	printf("%s[ Error ]%s ", C_RED, CLEAR);
	if (error == ERROR_INVALID_ARGS)
		printf("Invalid number of arguments!\n");
	else if (error == ERROR_OPEN)
		printf("Error opening the config file\n");
	else if (error == ERROR_MALLOC)
		perror("Error on malloc");
	else if (error == ERROR_MAP)
		printf("Error while checking the map :/\n");
	else
		printf("Success(\\\\(·o·;)\n");

	if (parsed)
	{
		parse_print(parsed);
		destroy_parsed(parsed);
	}

	exit(ERROR_EXIT_VALUE);
}

static void	init_parser_data(t_parsed_data *parsed, char *filename)
{
	size_t	index;
	
	/* Clean the struct data */
	ft_bzero(parsed, sizeof(*parsed));

	/* Init the main fd */
	parsed->config_filename = filename;
	parsed->fd = open(filename, O_RDONLY);
	if (parsed->fd < 0)
		parse_error(ERROR_OPEN, NULL);

	/* Init the strings and the fds */
	index = -1;
	while (++index < TEXTURES_COUNT)
		parsed->textures_fds[index] = -1;
	
	/* Init the pixels */
	index = -1;
	while (++index < PIXELS_COUNT)
		reset_pixel(&parsed->default_pixels[index]);
}

/*#########################################################*/

void	parse(int argc, char **argv, t_parsed_data *parsed)
{
	if (argc != 2 || !check_extension(argv[1], CONFIG_EXTENSION))
		parse_error(ERROR_INVALID_ARGS, NULL);

	init_parser_data(parsed, argv[1]);
	parse_file(parsed);
	check_map(parsed);

	/* TODO: Check that all the info is valid */

	/* DEBUGGING: print the parse data */
	// parse_print(parsed);

	exit(0);
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
			free(parsed->textures_name[index]);
		ft_close(&(parsed->textures_fds[index]));
	}

	/* Delete the map */
	if (parsed->map)
		ft_free_split(parsed->map);

	/* Set the defaults values */
	init_parser_data(parsed, parsed->config_filename);
}
