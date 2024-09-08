#include "../../include/cub3d.h"

void	compass(t_cube *cube)
{
	double	x;
	double	y;
	t_image *image;

	x = cube->pj.dirX;
	y = cube->pj.dirY;

	if (fabs(y) > fabs(x)) {
		if (y < 0)
			image = &cube->grafic->compass[NORTH_COMPASS_F1 + cube->frame];
		else
			image = &cube->grafic->compass[SOUTH_COMPASS_F1 + cube->frame];
	} else {
		if (x > 0)
			image = &cube->grafic->compass[EAST_COMPASS_F1 + cube->frame];
		else
			image = &cube->grafic->compass[WEST_COMPASS_F1 + cube->frame];
	}
	mlx_put_image_to_window(cube->grafic->mlx, cube->grafic->win, image->img, 20, WINDOW_HEIGTH - COMPASS_SIZE - 20);
}
