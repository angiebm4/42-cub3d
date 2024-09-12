#include "../../include/cub3d.h"

void	screen_init(t_cube *cube)
{
	cube->graphic = ft_calloc(1, sizeof(t_mlx));
	if (cube->graphic == NULL)
		cube_destroy(cube, 1);
	cube->graphic->mlx = mlx_init();
	if (cube->graphic->mlx == NULL)
		cube_destroy(cube, 1);
	cube->graphic->win = mlx_new_window(cube->graphic->mlx,
			WINDOW_WIDTH, WINDOW_HEIGTH, PROGRAM_NAME);
	if (cube->graphic->win == NULL)
		cube_destroy(cube, 1);
	if (create_image(&cube->graphic->screen, cube->graphic,
			WINDOW_WIDTH, WINDOW_HEIGTH))
		cube_destroy(cube, 1);
}
