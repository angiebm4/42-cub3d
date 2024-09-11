#include "../../include/cub3d.h"

void	screen_init(t_cube *cube)
{
	cube->grafic = ft_calloc(1, sizeof(t_mlx));
	if (cube->grafic == NULL)
		exit(1); /* TODO: malloc error*/
	cube->grafic->mlx = mlx_init();
	if (cube->grafic->mlx == NULL)
		exit(1); /* TODO: error  create mlx*/
	cube->grafic->win = mlx_new_window(cube->grafic->mlx,
			WINDOW_WIDTH, WINDOW_HEIGTH, PROGRAM_NAME);
	if (cube->grafic->win == NULL)
		exit(1); /* TODO: error win create*/
	if (create_image(&cube->grafic->screen, cube->grafic,
			WINDOW_WIDTH, WINDOW_HEIGTH))
		exit(1); /* TODO: Error */
}
