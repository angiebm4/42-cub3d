#include "../include/cub3d.h"

int	render(t_cube *cube)
{
	/* Frame */
	cube->frame_duration = (cube->frame_duration + 1) % FRAME_DURATION;
	if (cube->frame_duration == 0)
		cube->frame = (cube->frame + 1) % FRAMES;

	/* Screen */
	raycasting(cube);
	compass(cube);
	return (0);
}
