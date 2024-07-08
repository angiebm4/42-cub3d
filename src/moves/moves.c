#include "../include/cub3d.h"

static void	change_position(int keycode, t_cube *cube)
{
	double		pos[2];
	t_player	*player = &cube->pj;

	if (keycode == W || keycode == UP)
	{
		pos[0] = player->posX + player->dirX * MOVE_SPEED;
        pos[1] = player->posY + player->dirY * MOVE_SPEED;

		if (cube->map[(int)player->posY][(int)(pos[0] + player->dirX * SEPARATOR)] == '0')
            player->posX = pos[0];
        if (cube->map[(int)(pos[1] + player->dirY * SEPARATOR)][(int)player->posX] == '0')
            player->posY = pos[1];
	}

	if (keycode == S || keycode == DOWN)
	{
		pos[0] = player->posX - player->dirX * MOVE_SPEED;
        pos[1] = player->posY - player->dirY * MOVE_SPEED;

		if (cube->map[(int)player->posY][(int)(pos[0] - player->dirX * SEPARATOR)] == '0')
            player->posX = pos[0];
        if (cube->map[(int)(pos[1] - player->dirY * SEPARATOR)][(int)player->posX] == '0')
            player->posY = pos[1];
	}	
}

static void change_vision(int keycode, t_cube *cube)
{
	double	old_dirX;
	double	old_planeX;
	t_player	*player = &cube->pj;

	old_dirX = player->dirX;
	old_planeX = player->planeX;

	if (keycode == A || keycode == LEFT)
	{
		player->dirX = player->dirX * cos(-ROTATION_SPEED) - player->dirY * sin(-ROTATION_SPEED);
		player->dirY = old_dirX * sin(-ROTATION_SPEED) + player->dirY * cos(-ROTATION_SPEED);

		player->planeX = player->planeX * cos(-ROTATION_SPEED) - player->planeY * sin(-ROTATION_SPEED);
		player->planeY = old_planeX * sin(-ROTATION_SPEED) + player->planeY * cos(-ROTATION_SPEED);
	}

	if (keycode == D || keycode == RIGHT) {
		player->dirX = player->dirX * cos(ROTATION_SPEED) - player->dirY * sin(ROTATION_SPEED);
		player->dirY = old_dirX * sin(ROTATION_SPEED) + player->dirY * cos(ROTATION_SPEED);

		player->planeX = player->planeX * cos(ROTATION_SPEED) - player->planeY * sin(ROTATION_SPEED);
		player->planeY = old_planeX * sin(ROTATION_SPEED) + player->planeY * cos(ROTATION_SPEED);
	}
}

void	moves(int keycode, t_cube *cube)
{
	if (keycode == W || keycode == UP || keycode == S || keycode == DOWN)
		change_position(keycode, cube);
	if (keycode == A || keycode == LEFT || keycode == D || keycode == RIGHT)
		change_vision(keycode, cube);
}