#include "../include/cub3d.h"

typedef struct	s_player_pos
{
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
} t_player_pos;

static void	init_position(int *x, int *y, t_parsed_data *parsed)
{
	int index;

    *x = -1;
	*y = -1;
    index = -1;
    while (PJ_CHARS[++index] && *x == -1 && *y == -1)
        search_map(parsed->map, PJ_CHARS[index], x, y);
}

static void set_vision(t_player_pos pos, t_player *player)
{
	player->dirX = pos.dirX;
	player->dirY = pos.dirY;
	player->planeX = pos.planeX;
	player->planeY = pos.planeY;
}

static void init_vision(int x, int y, t_cube *cube)
{
    if (cube->map[y][x] == 'N')
		set_vision((t_player_pos){0.0, -1.0, 0.66, 0}, &cube->pj);
    else if (cube->map[y][x] == 'S')
		set_vision((t_player_pos){0.0, 1.0, -0.66, 0}, &cube->pj);
    else if (cube->map[y][x] == 'E')
		set_vision((t_player_pos){1.0, 0.0, 0.0, 0.66}, &cube->pj);
    else
		set_vision((t_player_pos){-1.0, 0.0, 0.0, -0.66}, &cube->pj);
}

void    init_player(t_cube *cube, t_parsed_data *parsed)
{
    int x, y;

	init_position(&x, &y, parsed);
    cube->pj.posX = x + 0.5;
    cube->pj.posY = y + 0.5;

    init_vision(x, y, cube);
    cube->map[y][x] = '0';
}
