#include "../../include/cub3d.h"

static void	raycasting_main(int x, t_cube *cube)
{
	/* Get the calculations */
	raycasting_calcs(x, cube);

	/* Print the textures */
	raycasting_print_textures(x, cube);
}

int render(t_cube *cube)
{
	int	x;

	/* Set the floor and ceiling colors */
	raycasting_print_pixels(cube);

	x = -1;
	while (++x < WINDOW_WIDTH)
		raycasting_main(x, cube);

	/* Put the colored image on the window */
	mlx_put_image_to_window(cube->grafic->mlx, cube->grafic->win, cube->grafic->img, 0, 0);
	// mlx_do_sync(cube->grafic->mlx);

	return (0);
}
