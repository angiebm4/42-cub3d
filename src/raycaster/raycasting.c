#include "../../include/cub3d.h"

void	raycasting(t_cube *cube)
{
	int		x;
	t_mlx	*mlx;

	x = -1;
	mlx = cube->graphic;
	raycasting_print_pixels(cube);
	while (++x < WINDOW_WIDTH)
	{
		raycasting_calcs(x, cube);
		raycasting_print_textures(x, cube);
	}
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->screen.img, 0, 0);
}
