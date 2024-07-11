#include "../../include/cub3d.h"

void	move_player(int inc, t_cube *cube)
{
	
	double		posX;
	double		posY;
	t_player	*player = &cube->pj;

	posX = player->posX + inc * player->dirX * MOVE_SPEED;
	posY = player->posY + inc * player->dirY * MOVE_SPEED;

	if (cube->map[(int)player->posY][(int)(posX + inc * player->dirX * SEPARATOR)] == '0')
		player->posX = posX;
	if (cube->map[(int)(posY + inc * player->dirY * SEPARATOR)][(int)player->posX] == '0')
		player->posY = posY;
}
