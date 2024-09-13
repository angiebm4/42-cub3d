#include "../../include/cub3d.h"

void	mouse_init(t_cube *cube)
{
	ft_bzero(&cube->graphic->mouse, sizeof(t_mouse));
	cube->graphic->mouse.lastX = -1;
	cube->graphic->mouse.mouse_vision = 1;
	cube->graphic->mouse.fixed = 0;
}
