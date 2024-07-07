#include "../include/cub3d.h"

static void	raycasting_main(int x, t_cube *cube)
{
	raycasting_calcs(x, cube);
	raycasting_print_textures(x, cube);
}

void render(t_cube *cube)
{
	int	x;

	x = -1;
	raycasting_print_pixels(cube);
	while (++x < WINDOW_WIDTH)
		raycasting_main(x, cube);

	/* Put the colored image on the window */
	mlx_put_image_to_window(cube->grafic->mlx, cube->grafic->win, cube->grafic->img, 0, 0);
	mlx_do_sync(cube->grafic->mlx); /* It is used to be faster */
}
