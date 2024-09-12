#include "../include/cub3d.h"

void	cube_init(t_cube *cube, t_parsed_data *parsed)
{
	ft_bzero(cube, sizeof(t_cube));
	screen_init(cube);
	map_init(cube, parsed);
	textures_init(cube, parsed);
	doors_init(cube, parsed);
	player_init(cube, parsed);
	ft_bzero(&cube->grafic->raycasting, sizeof(t_raycasting));
	mouse_init(cube);
	if (load_compass(cube))
		cube_destroy(cube, 1);
	destroy_parsed(parsed);
}
