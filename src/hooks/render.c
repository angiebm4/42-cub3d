#include "../include/cub3d.h"

static void	frame_increment(t_cube *cube)
{
	cube->frame_duration = (cube->frame_duration + 1) % FRAME_DURATION;
	if (cube->frame_duration == 0)
		cube->frame = (cube->frame + 1) % FRAMES;
}

int	render(t_cube *cube)
{
	frame_increment(cube);
	raycasting(cube);
	compass(cube);
	return (0);
}
