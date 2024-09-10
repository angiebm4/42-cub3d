#include "../../include/cub3d.h"

void	parse_error(int error, t_parsed_data *parsed, int print)
{
	printf("%s[ Error ]%s ", RED, CLEAR);
	if (error == ERROR_INVALID_ARGS)
		printf("Invalid number of arguments!\n");
	else if (error == ERROR_OPEN)
		printf("Error opening the config file\n");
	else if (error == ERROR_MALLOC)
		perror("Error on malloc");
	else if (error == ERROR_MAP)
		printf("Error while checking the map :/\n");
	else if (error == ERROR_TEXTURES)
		printf("Error while trying to read a texture\n");
	else if (error == ERROR_PIXELS)
		printf("Error while analyzing pixels\n");
	else
		printf("Success(\\\\(·o·;)\n");
	if (parsed && print)
		parse_print(parsed);
	if (parsed)
		destroy_parsed(parsed);
	exit(ERROR_EXIT_VALUE);
}

static void	init_parser_data(t_parsed_data *parsed, char *filename)
{
	size_t	index;

	ft_bzero(parsed, sizeof(*parsed));
	parsed->config_filename = filename;
	parsed->fd = open(filename, O_RDONLY);
	if (parsed->fd < 0)
		parse_error(ERROR_OPEN, NULL, 0);
	index = -1;
	while (++index < PIXELS_COUNT)
		reset_pixel(&parsed->default_pixels[index]);
}

/*#########################################################*/

void	parse(int argc, char **argv, t_parsed_data *parsed)
{
	if (argc != 2 || !check_extension(argv[1], CONFIG_EXTENSION))
		parse_error(ERROR_INVALID_ARGS, NULL, 0);
	init_parser_data(parsed, argv[1]);
	parse_file(parsed);
	check_graphic(parsed);
	check_map(parsed);
	clean_map(parsed->map);
}

void	destroy_parsed(t_parsed_data *parsed)
{
	size_t	index;

	index = -1;
	ft_close(&(parsed->fd));
	while (++index < TEXTURES_COUNT)
	{
		if (parsed->textures_name[index])
			free(parsed->textures_name[index]);
	}
	if (parsed->map)
		ft_free_split(parsed->map);
	ft_lstclear(&parsed->doors, free);
	init_parser_data(parsed, parsed->config_filename);
}
