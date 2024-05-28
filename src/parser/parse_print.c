# include "../../include/cub3d.h"

# define PARSE_OK       C_GREENFOSFI"  OK "CLEAR
# define PARSE_ERROR    C_RED"ERROR"CLEAR
# define TEXTURE_LINE_SPACING   "·------·-----------·-----------·"
# define PIXEL_LINE_SPACING		"·---------·-----------·-----------·"

/* ################################################################################################## */

static void print_textures(t_parsed_data *parsed)
{
	int index;
	char **phs;

	index = -1;
	phs = ft_split(VIEWS_PLACEHOLDERS, '.');
	if (!phs)
		return ;

	printf("· Textures summary:\n");
	printf("\t%s%s%s\n", C_CYAN, TEXTURE_LINE_SPACING, CLEAR);
	printf("\t%s|  PH  |  APPEARS  |  CORRECT  |%s\n", C_CYAN, CLEAR);
	printf("\t%s%s%s\n", C_CYAN, TEXTURE_LINE_SPACING, CLEAR);

	while (++index < TEXTURES_COUNT)
	{
		printf("\t|  %s  |   %s   |   %s   |\n", phs[index],
										parsed->textures_name[index] == NULL ? PARSE_ERROR : PARSE_OK,
										parsed->textures_fds[index] < 0 ? PARSE_ERROR : PARSE_OK);
		printf("\t%s\n", TEXTURE_LINE_SPACING);
	}
	ft_free_split(phs);
}

/* ################################################################################################## */

static void	check_pixels(t_pixel *pixel, char **appears, char **is_correct)
{
	if (pixel_is_default(pixel))
		*appears = PARSE_ERROR;
	else
		*appears = PARSE_OK;

	if(pixel_is_valid(pixel))
		*is_correct = PARSE_ERROR;
	else
		*is_correct = PARSE_OK;
}


static void	print_pixels(t_parsed_data *parsed)
{
	char	*appears;
	char	*is_correct;

	printf("· Pixels summary:\n");
	printf("\t%s%s%s\n", C_CYAN, PIXEL_LINE_SPACING, CLEAR);
	printf("\t%s|  PIXEL  |  APPEARS  |  CORRECT  |%s\n", C_CYAN, CLEAR);
	printf("\t%s%s%s\n", C_CYAN, PIXEL_LINE_SPACING, CLEAR);

	/* Floor pixel */
	check_pixels(&parsed->floor, &appears, &is_correct);
	printf("\t|  FLOOR  |   %s   |   %s   |\n", appears, is_correct);
	printf("\t%s\n", PIXEL_LINE_SPACING);

	check_pixels(&parsed->ceiling, &appears, &is_correct);
	printf("\t| CEILING |   %s   |   %s   |\n", appears, is_correct);
	printf("\t%s\n", PIXEL_LINE_SPACING);
}

/* ################################################################################################## */

void	parse_print(t_parsed_data *parsed)
{
	print_textures(parsed);
	printf("\n");
	print_pixels(parsed);
	/* TODO: check the map*/
}
