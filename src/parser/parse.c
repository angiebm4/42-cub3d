#include "../../include/cub3d.h"

static void	parse_error(int error, t_parsed_data *parsed)
{
	printf("[ Error ] ");
	if (error == ERROR_INVALID_ARGS)
		printf("Invalid number of arguments!\n");
	else if (error == ERROR_OPEN)
		printf("Error opening the config file\n");
	else if (error == ERROR_MALLOC)
		perror("Error on malloc");
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
	parsed->fd = open(filename, O_RDONLY);
	if (parsed->fd < 0)
		parse_error(ERROR_OPEN, NULL);

	/* Init the strings and the fds */
	index = -1;
	while (++index < TEXTURES_COUNT)
		parsed->textures_fds[index] = -1;
	
	/* Init the pixels */
	reset_pixel(&parsed->floor);
	reset_pixel(&parsed->ceiling);
}

// static int	valid_exten

/*#########################################################*/

void	parse(int argc, char **argv, t_parsed_data *parsed)
{
	
	if (argc != 2 || ft_strcmp(CONFIG_EXTENSION, &argv[1][ft_strlen(argv[1]) - 4]))
		parse_error(ERROR_INVALID_ARGS, NULL);

	init_parser_data(parsed, argv[1]);
	parse_file(parsed);
	
	//parse_print(parsed);
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
