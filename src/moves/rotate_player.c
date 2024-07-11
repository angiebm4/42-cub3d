#include "../../include/cub3d.h"

void	rotate_player(double angle, t_player *player)
{
	double		old_dirX;
	double		old_planeX;

	old_dirX = player->dirX;
	old_planeX = player->planeX;

	player->dirX = player->dirX * cos(angle) - player->dirY * sin(angle);
	player->dirY = old_dirX * sin(angle) + player->dirY * cos(angle);
	player->planeX = player->planeX * cos(angle) - player->planeY * sin(angle);
	player->planeY = old_planeX * sin(angle) + player->planeY * cos(angle);
}
