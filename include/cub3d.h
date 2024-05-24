#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/includes/libft.h"
# include "../mlx/mlx.h"

/* WINDOW MEASURES */
# define HEIGTH 500
# define WEIGTH 500

/* ERROR DEFINE */
# define ERROR_SUCCESS			0
# define ERROR_INVALID_ARGS		1
# define ERROR_OPEN				2
# define ERROR_MALLOC			3
# define ERROR_FILE_CONTENT		4
# define ERROR_MLX_TEX_CREATE	5
# define ERROR_MLX_INIT			6

/* VALID CHARACTERS */
# define VALID_CHARS "01NSWED "

/* REXTURES */
# define NORTH_TEXTURE  0
# define SOUTH_TEXTURE  1
# define WEST_TEXTURE   2
# define EAST_TEXTURE   3
# define DOOR_TEXTURE   4
# define TEXTURES_COUNT 5

typedef struct  s_cube  t_cube;
typedef struct  s_mlx   t_mlx;
typedef struct  s_pixel t_pixel;

struct   s_cube
{
	char    **map;		/* Map data*/

	t_mlx   *grafic;	/* Grafic data */
};

struct  s_mlx
{
	void    *mlx;		/* Screen reference */
	void    *win;		/* Window reference*/

	void        *textures[5];	/* Textures */
	t_pixel     *floor;			/* Floor pixel color */
	t_pixel     *ceiling;		/* Ceiling pixel color */
};

struct  s_pixel
{
	int red;	/* r */
	int blue;	/* g */
	int green;	/* b */
};

/* FIXME: DEBBUGING */
void    print_data(t_cube *cube);

/* ERROR */
int     error(int msg);

/* PARSER */
int    init_data(t_cube *cube, char *fd);

#endif