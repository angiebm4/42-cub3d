#include "../include/cub3d.h"


void	my_pixel_put(t_image *img, double x, double y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pix_addr)) = color;
}


int set_color(t_cube *cube, int mapX, int mapY)
{
    if (cube->map[mapY][mapX] == '0')
        return(H_GRASS_GREEN);
    if (cube->map[mapY][mapX] == '1')
        return(H_BROWN);
    if (cube->map[mapY][mapX] == 'D')
        return(H_GRAY);
    else
        return(H_RED);
}

void    errase_minimap(t_cube *cube)
{
    int color;
    int i;
    int j;

    color = H_BLACK;
    i = 0;
    while (i < MINIMAP_HEIGHT)
    {
        j = 0;
        while (j < MINIMAP_WIDTH)
        {
            my_pixel_put(cube->grafic->mini_map, j, i, color);
            j++;
        }
        i++;
    }
}


void    mini_map(t_cube *cube)
{
    errase_minimap(cube);
    int start_x = floor(cube->pj.posX) - MINIMAP_WIDTH / 2 / INCREMENT_VALUE_X;
    int start_y = floor(cube->pj.posY) - MINIMAP_HEIGHT / 2 / INCREMENT_VALUE_Y;
    int y;
    int x;
    int aux_y;
    int aux_x;
    int iterable[2];

    y = 0;
    aux_y = 0;
    while (y < MINIMAP_HEIGHT)
    {
        x = 0;
        aux_x = 0;
        while(x < MINIMAP_WIDTH)
        {
            int mapX = start_x + aux_x;
            int mapY = start_y + aux_y;
            if (mapX >= 0 && mapX < cube->map_w && mapY >= 0 && mapY < cube->map_h)
            {
                iterable[1] = -1;
                while (++iterable[1] < INCREMENT_VALUE_Y)
                {
                    iterable[0] = -1;
                    while (++iterable[0] < INCREMENT_VALUE_X)
                    {
                        if (floor(cube->pj.posX) == mapX && floor(cube->pj.posY) == mapY)
                        {
                            my_pixel_put(cube->grafic->mini_map, x + iterable[0],
                            y + iterable[1], H_SKIN);
                        }
                        else
                        {
                            my_pixel_put(cube->grafic->mini_map, x + iterable[0],
                            y + iterable[1], set_color(cube, mapX, mapY));
                        }
                    }
                }
            }
            x += INCREMENT_VALUE_X;
            aux_x++;
        }
        y += INCREMENT_VALUE_Y;
        aux_y++;
    }
    mlx_put_image_to_window(cube->grafic->mlx,
        cube->grafic->win, cube->grafic->mini_map->img, 0, 0);
}

