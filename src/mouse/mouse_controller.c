#include "../../include/cub3d.h"

void	mouse_controller(int keycode, t_cube *cube)
{
	if (keycode == MOUSE_VISIBILITY_KEY)
		mouse_display(cube);
	else if (keycode == MOUSE_FIX_KEY)
		mouse_fix(&cube->graphic->mouse);
}
