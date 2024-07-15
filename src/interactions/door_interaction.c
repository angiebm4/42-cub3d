#include "../../include/cub3d.h"

static int	points_distance(int x1, int y1, int x2, int y2)
{
	return ((int)sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}

static void	change_state(int x, int y, t_cube *cube)
{
	if (cube->map[y][x] == 'D')
		cube->map[y][x] = '0';
	else
		cube->map[y][x] = 'D';
}

void	door_interaction(t_cube *cube)
{
	int	x_player;
	int	y_player;
	int	points_diff;
	t_list	*it;
	t_door	*door;

	it = cube->doors;
	x_player = (int)cube->pj.posX;
	y_player = (int)cube->pj.posY;

	while (it)
	{
		door = it->content;
		points_diff = points_distance(x_player, y_player, door->x, door->y);
		if (points_diff <= INTERACTION_DISTANCE && points_diff > 0)
			change_state(door->x, door->y, cube);

		it = it->next;
	}
}

