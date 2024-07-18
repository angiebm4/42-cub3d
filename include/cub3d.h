#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"

# ifndef DEBUG
#  define DEBUG 0
# endif

/* WINDOW MEASURES */
# define WINDOW_HEIGHT 960
# define WINDOW_WIDTH 1280
# define CUBE_SIZE	64

/* MINI MAP MEASURES */
# define MINIMAP_HEIGHT WINDOW_HEIGHT / 7
# define MINIMAP_WIDTH WINDOW_WIDTH / 7

# define INCREMENT_VALUE_Y 10
# define INCREMENT_VALUE_X 10

/* Player moves */
# define MOVE_SPEED				0.1
# define ROTATION_SPEED			0.06
# define MOUSE_ROTATION_SPEED	0.01
# define SEPARATOR				0.1

/* PROGARM NAME */
# define PROGRAM_NAME	"Cub3d"

/* ERROR DEFINE */
# define ERROR_SUCCESS			0
# define ERROR_INVALID_ARGS		1
# define ERROR_OPEN				2
# define ERROR_MALLOC			3
# define ERROR_FILE_CONTENT		4
# define ERROR_MLX_TEX_CREATE	5
# define ERROR_MLX_INIT			6
# define ERROR_MAP				7
# define ERROR_TEXTURES			8
# define ERROR_PIXELS			9
# define ERROR_EXIT_VALUE		EXIT_FAILURE

/* VALID CHARACTERS */
# define VALID_MAP_CHARS "01NSWED "
# define PJ_CHARS "NSWE"

/* TEXTURES */
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
# define PLAYER_
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

# define M 		109
# define N 		110

# define ON_KEYDOWN		2
# define ON_MOUSEMOVE	6
# define ON_DESTROY		17

# define MOUSE_VISIBILITY_KEY	M
# define MOUSE_FIX_KEY			N

typedef struct s_cube  		t_cube;
typedef struct s_mlx   		t_mlx;
typedef struct s_pixel 		t_pixel;
typedef struct s_player 	t_player;
typedef struct s_image 		t_image;
typedef struct s_raycasting	t_raycasting;
typedef struct s_mouse 		t_mouse;

struct  s_pixel
{
	int red;	/* r */
	int green;	/* g */
	int blue;	/* b */
};

struct	s_mouse
{
	int		mouse_vision;
	int		lastX;
	int		fixed;
};

struct	s_player
{
	/* Player position */
	double	posX;
	double	posY;

	/* View directions */
	double	dirX;
	double	dirY;

	/* Camera plane */
	double	planeX;
	double	planeY;
};

struct   s_cube
{
	char    **map;		/* Map data*/
	int		map_h;
	int		map_w;

	t_mlx   *grafic;	/* Grafic data */
	t_player	pj;
};

struct	s_raycasting
{
	double	cameraX;
	double	rayDirX;
	double	rayDirY;

	int		mapX;
	int		mapY;

	double	deltaDistX;
	double	deltaDistY;

	double	sideDistX;
	double	sideDistY;

	double	perpWallDist;

	int 	stepX;
	int 	stepY;

	int		side;
};

struct	s_image
{
	void	*img;
	char	*pix_addr;
	int		bpp;
	int		line_len;
	int		endian;
};

struct  s_mlx
{
	void    *mlx;		/* Screen reference */
	void    *win;		/* Window reference*/
	
	t_mouse	mouse;

	void	*img;
	char	*data_addr;
	int		bpp;
	int		size_line;
	int		endian;

	t_image	*mini_map;

	t_raycasting	raycasting;


	void        *textures[TEXTURES_COUNT];		/* Textures */
	t_pixel     default_pixels[PIXELS_COUNT];	/* Default pixels*/
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
void	parse_error(int error, t_parsed_data *parsed, int print);


/* Function to check an extension */
int		check_extension(char *buffer, char *extension);

/* Function to save the config data */
void    parse_file(t_parsed_data *parsed);
int		save_placeholder(t_parsed_data *parsed, char **buffer, int ph);
char	**save_map(t_parsed_data *parsed, char *buffer);

/* Map check */
void	check_map(t_parsed_data *parsed);
int		flood_fill(char **map, t_parsed_data *parsed);
void	clean_map(char **map);

/* Check the graphic part parsed */
void	check_graphic(t_parsed_data *parsed);

/* Map utils */
int		map_check_characters(char **map, char *set);
char	**copy_map(char **matrix);
int		search_map(char **map, char ch, int *x, int *y);
size_t	map_length(char **matrix);

/* Line utils */
int 	line_is_empty(char *line, char *empty_set);
int 	line_is_comment(char *line, char *comment_set);
int 	line_is_placeholder(char *supposed_ph, t_parsed_data *parsed);
int		line_can_omitted(char *line);

/*_____________________________________________________________________*/

/* Pixel utils */
void	reset_pixel(t_pixel *pixel);
int		pixel_is_valid(t_pixel *pixel);
int		pixel_is_default(t_pixel *pixel);
void	pixel_copy(t_pixel *dest, t_pixel *src);
int	pixel_conversor(t_pixel *pixel);

/* INIT GRAFIC */
void	cube_mlx_init(t_cube *cube, t_parsed_data *parsed);

/* HOOKS */
void    hooking(t_cube *cube);
int		end_program(t_cube *cube);

/* MINI MAP */
void    mini_map(t_cube *cube);

/* Raycasting */
int		render(t_cube *cube);
void	raycasting_calcs(int x, t_cube *cube);
void	raycasting_print_pixels(t_cube *cube);
void	raycasting_print_textures(int x, t_cube *cube);

/* Player moves */
void	moves(int keycode, t_cube *cube);
void	move_player(int inc, t_cube *cube);
void	rotate_player(double angle, t_player *player);

/* Mouse actions */
void	mouse_controller(int keycode, t_cube *cube);
int		mouse_move(int x, int y, t_cube *cube);
void	mouse_display(t_cube *cube);
void	mouse_fix(t_mouse *mouse);

/* LEAVE MEMORY */
void    clean_trash(t_cube *cube);


#endif