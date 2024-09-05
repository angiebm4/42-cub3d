#include "../../include/cub3d.h"

static void	raycasting_main(int x, t_cube *cube)
{
	raycasting_calcs(x, cube);
	raycasting_print_textures(x, cube);
}

int	render(t_cube *cube)
{
	int		x;
	t_mlx	*mlx;

	x = -1;
	mlx = cube->grafic;
	raycasting_print_pixels(cube);
	while (++x < WINDOW_WIDTH)
		raycasting_main(x, cube);
	mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->screen.img, 0, 0);
	return (0);
}
