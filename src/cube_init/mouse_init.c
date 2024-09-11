#include "../../include/cub3d.h"

void	mouse_init(t_cube *cube)
{
	ft_bzero(&cube->grafic->mouse, sizeof(t_mouse));
	cube->grafic->mouse.lastX = -1;
	cube->grafic->mouse.mouse_vision = 1;
	cube->grafic->mouse.fixed = 0;
}
