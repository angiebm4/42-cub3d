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
# define ERROR_EXIT_VALUE		EXIT_FAILURE

/* VALID CHARACTERS */
# define VALID_CHARS "01NSWED "

/* REXTURES */
# define NORTH_TEXTURE  0
# define SOUTH_TEXTURE  1
# define WEST_TEXTURE   2
# define EAST_TEXTURE   3
# define DOOR_TEXTURE   4
# define TEXTURES_COUNT 5
# define VIEWS_PLACEHOLDERS "NO.SO.WE.EA.DO.F.C"
# define SEPARATOR_PLACEHOLDER '.'

# define COMMENT_SET	"@#;//"
# define EMPTY_SET		" \t"

# define CONFIG_EXTENSION	".cub"

/* Default pixel value */
# define PIXEL_DEFAULT	-1
# define PIXEL_MIN		0
# define PIXEL_MAX		255

typedef struct  s_cube  t_cube;
typedef struct  s_mlx   t_mlx;
typedef struct  s_pixel t_pixel;

struct  s_pixel
{
	int red;	/* r */
	int blue;	/* g */
	int green;	/* b */
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

	void        *textures[TEXTURES_COUNT];	/* Textures */
	t_pixel     floor;						/* Floor pixel color */
	t_pixel     ceiling;					/* Ceiling pixel color */
};

/*_____________________________________________________________________*/

typedef struct s_parser
{
	int		fd;	/* File descriptor of the config file */
	
	char	*textures_name[TEXTURES_COUNT];	/* Name of the textures paths */
	int		textures_fds[TEXTURES_COUNT];	/* File descriptors of the textures */

	t_pixel	floor;		/* Floor pixel color readed */
	t_pixel	ceiling;	/* Ceiling pixel color readed */

	char	**map;		/* Map readed */

}				t_parsed_data;


void	parse(int argc, char **argv, t_parsed_data *parsed);
void	destroy_parsed(t_parsed_data *parsed);
void	parse_print(t_parsed_data *parsed);
void    parse_file(t_parsed_data *parsed);

int 	line_is_empty(char *line, char *empty_set);
int 	line_is_comment(char *line, char *comment_set);
int 	line_is_placeholder(char *supposed_ph);

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