#include "../../include/cub3d.h"

void	compass(t_cube *cube)
{
	mlx_put_image_to_window(cube->grafic->mlx, cube->grafic->win, cube->grafic->textures[NORTH_TEXTURE].img, 0, 0);
}
