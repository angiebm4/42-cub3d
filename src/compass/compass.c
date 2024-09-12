#include "../../include/cub3d.h"

void	compass(t_cube *cube)
{
	double	x;
	double	y;
	t_image	*image;

	x = cube->pj.dir_x;
	y = cube->pj.dir_y;
	if (fabs(y) > fabs(x))
	{
		if (y < 0)
			image = &cube->graphic->compass[NORTH_COMPASS_F1 + cube->frame];
		else
			image = &cube->graphic->compass[SOUTH_COMPASS_F1 + cube->frame];
	}
	else
	{
		if (x > 0)
			image = &cube->graphic->compass[EAST_COMPASS_F1 + cube->frame];
		else
			image = &cube->graphic->compass[WEST_COMPASS_F1 + cube->frame];
	}
	mlx_put_image_to_window(cube->graphic->mlx, cube->graphic->win, image->img,
		20, WINDOW_HEIGTH - COMPASS_SIZE - 20);
}
