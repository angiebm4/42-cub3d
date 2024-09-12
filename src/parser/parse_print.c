#include "../../include/cub3d.h"

#define TEXTURE_LINE_SPACING	"·------·-----------·"
#define PIXEL_LINE_SPACING		"·---------·-----------·-----------·"

/* ######################################################################### */

static void	print_textures(t_parsed_data *parsed)
{
	int		index;
	char	**phs;

	index = -1;
	phs = ft_split(VIEWS_PLACEHOLDERS, SEPARATOR_PLACEHOLDER);
	if (!phs)
		return ;
	printf("· Textures summary:\n");
	printf("\t%s%s%s\n", CYAN, TEXTURE_LINE_SPACING, CLEAR);
	printf("\t%s|  PH  |  APPEARS  |%s\n", CYAN, CLEAR);
	printf("\t%s%s%s\n", CYAN, TEXTURE_LINE_SPACING, CLEAR);
	while (++index < TEXTURES_COUNT)
	{
		printf("\t|  %s  |   %s   |\n", phs[index],
			parse_check_texture(parsed->textures_name[index]));
		printf("\t%s\n", TEXTURE_LINE_SPACING);
	}
	ft_free_split(phs);
}

/* ######################################################################### */

static void	print_pixels(t_parsed_data *parsed)
{
	char	*check[2];

	printf("· Pixels summary:\n");
	printf("\t%s%s%s\n", CYAN, PIXEL_LINE_SPACING, CLEAR);
	printf("\t%s|  PIXEL  |  APPEARS  |  CORRECT  |%s\n", CYAN, CLEAR);
	printf("\t%s%s%s\n", CYAN, PIXEL_LINE_SPACING, CLEAR);
	parse_check_pixel(&parsed->default_pixels[FLOOR_PIXEL], check);
	printf("\t|  FLOOR  |   %s   |   %s   |\n", check[0], check[1]);
	printf("\t%s\n", PIXEL_LINE_SPACING);
	parse_check_pixel(&parsed->default_pixels[CEILING_PIXEL], check);
	printf("\t| CEILING |   %s   |   %s   |\n", check[0], check[1]);
	printf("\t%s\n", PIXEL_LINE_SPACING);
}

/* ######################################################################### */

void	parse_print(t_parsed_data *parsed)
{
	print_textures(parsed);
	printf("\n");
	print_pixels(parsed);
}
