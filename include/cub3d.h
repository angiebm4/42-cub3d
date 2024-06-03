#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"

/* WINDOW MEASURES */
# define WINDOW_HEIGTH 500
# define WINDOW_WEIGTH 500

/* ERROR DEFINE */
# define ERROR_SUCCESS			0
# define ERROR_INVALID_ARGS		1
# define ERROR_OPEN				2
# define ERROR_MALLOC			3
# define ERROR_FILE_CONTENT		4
# define ERROR_MLX_TEX_CREATE	5
# define ERROR_MLX_INIT			6
# define ERROR_MAP				7
# define ERROR_EXIT_VALUE		EXIT_FAILURE

/* VALID CHARACTERS */
# define VALID_MAP_CHARS "01NSWED "

/* REXTURES */
# define NORTH_TEXTURE  0
# define SOUTH_TEXTURE  1
# define WEST_TEXTURE   2
# define EAST_TEXTURE   3
# define DOOR_TEXTURE   4
# define TEXTURES_COUNT 5

# define FLOOR_PIXEL	0	/* 5 */
# define CEILING_PIXEL	1	/* 6 */
# define PIXELS_COUNT	2

# define VIEWS_PLACEHOLDERS "NO.SO.WE.EA.DO.F.C"
# define SEPARATOR_PLACEHOLDER '.'

# define COMMENT_SET	"@#;//"
# define EMPTY_SET		" \t\n"
# define PIXEL_SEPARATOR	','

# define CONFIG_EXTENSION	".cub"
# define TEXTURE_EXTENSION	".xpm"

/* Default pixel value */
# define PIXEL_DEFAULT	-1
# define PIXEL_MIN		0
# define PIXEL_MAX		255

/* Minilibs key codes */
# define ESC	65307
# define W		119
# define A		97
# define S		115
# define D		100

# define UP		65362
# define LEFT	65361
# define DOWN	65364
# define RIGHT	65363

typedef struct  s_cube  t_cube;
typedef struct  s_mlx   t_mlx;
typedef struct  s_pixel t_pixel;

struct  s_pixel
{
	int red;	/* r */
	int green;	/* g */
	int blue;	/* b */
};

struct   s_cube
{
	char    **map;		/* Map data*/

	t_mlx   *grafic;	/* Grafic data */
};

struct  s_mlx
{
	void    *mlx;		/* Screen reference */
	void    *win;		/* Window reference*/

	void        *textures[TEXTURES_COUNT];		/* Textures */
	t_pixel     default_pixels[TEXTURES_COUNT];	/* Default pixels*/
};

/*_____________________________________________________________________*/

typedef struct s_parser
{
	char	*config_filename;
	int		fd;	/* File descriptor of the config file */
	
	char	*textures_name[TEXTURES_COUNT];	/* Name of the textures paths */

	t_pixel	default_pixels[PIXELS_COUNT];	/* Default pixels*/

	char	**map;		/* Map readed */
}				t_parsed_data;


/* Principal parser struct functions */
void	parse(int argc, char **argv, t_parsed_data *parsed);
void	destroy_parsed(t_parsed_data *parsed);
void	parse_print(t_parsed_data *parsed);
void	parse_error(int error, t_parsed_data *parsed);


/* Function to check an extension */
int		check_extension(char *buffer, char *extension);

/* Function to save the config data */
void    parse_file(t_parsed_data *parsed);
int		save_placeholder(t_parsed_data *parsed, char **buffer, int ph);
char	**save_map(t_parsed_data *parsed, char *buffer);

/* Map check */
void	check_map(t_parsed_data *parsed);
int		flood_fill(char **map);

/* Map utils */
int		map_check_characters(char **map, char *set);
char	**copy_map(char **matrix);
int		search_map(char **map, char ch, int *x, int *y);
size_t	map_length(char **matrix);

/* Line utils */
int 	line_is_empty(char *line, char *empty_set);
int 	line_is_comment(char *line, char *comment_set);
int 	line_is_placeholder(char *supposed_ph);
int		line_can_omitted(char *line);

/*_____________________________________________________________________*/

/* Pixel utils */
void	reset_pixel(t_pixel *pixel);
int		pixel_is_valid(t_pixel *pixel);
int		pixel_is_default(t_pixel *pixel);
void	pixel_copy(t_pixel *dest, t_pixel *src);

/* FIXME: DEBBUGING */
void    print_data(t_cube *cube);

/* ERROR */
int     error(int msg);

/* PARSER */
int    init_data(t_cube *cube, char *fd);

#endif