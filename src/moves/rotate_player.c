#include "../../include/cub3d.h"

void	rotate_player(double angle, t_player *player)
{
	double		old_dir_x;
	double		old_plane_x;

	old_dir_x = player->dir_x;
	old_plane_x = player->plane_x;
	player->dir_x = player->dir_x * cos(angle) - player->dir_y
		* sin(angle);
	player->dir_y = old_dir_x * sin(angle) + player->dir_y
		* cos(angle);
	player->plane_x = player->plane_x * cos(angle) - player->plane_y
		* sin(angle);
	player->plane_y = old_plane_x * sin(angle) + player->plane_y
		* cos(angle);
}
