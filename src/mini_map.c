#include "../include/cub3d.h"


void	my_pixel_put(t_image *img, double x, double y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pix_addr)) = color;
}


void    draw_player(t_cube *cube)
{
    int start_x = MINIMAP_WIDTH / 2 - 2;
    int start_y = MINIMAP_HEIGHT / 2 - 2;
    int i;
    int j;

    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            my_pixel_put(cube->grafic->mini_map, i + start_x, j + start_y, H_ORANGE);
            j++;
        }
        i++;
    }
}

int set_color(t_cube *cube, int mapX, int mapY)
{
    if (cube->map[mapY][mapX] == '0')
        return(H_MAGENTA);
    if (cube->map[mapY][mapX] == '1')
        return(H_WHITE);
    if (cube->map[mapY][mapX] == 'D')
        return(H_BLUE);
    else
        return(H_GREEN);
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
    /* TODO: me sale un cacho de mapa a la izquierda y no se por que*/
    /* TODO: la posicion el pj es un double y lo estas ajustando a int puede fallar por eso*/
    errase_minimap(cube);
    int start_x = cube->pj.posX - MINIMAP_WIDTH / 2 / INCREMENT_VALUE_X;
    int start_y = cube->pj.posY - MINIMAP_HEIGHT / 2 / INCREMENT_VALUE_Y;

    // printf("%d\n", start_x);
    // printf("%d\n", start_y);

    
    /* TODO: no se me imprime en el centro segun pj */
    int y;
    int x;
    int aux_y;
    int aux_x;

    int iterable[2]; // [x, y]

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
            //    printf("uwu\n");
            // printf("mapX: %d, mapY: %d\n", mapX, mapY);
            if (mapX >= 0 && mapX < cube->map_w && mapY >= 0 && mapY < cube->map_h)
            {
                iterable[1] = -1;
                while (++iterable[1] < INCREMENT_VALUE_Y)
                {
                    iterable[0] = -1;
                    while (++iterable[0] < INCREMENT_VALUE_X)
                    {
                        my_pixel_put(cube->grafic->mini_map, x + iterable[0],
                         y + iterable[1], set_color(cube, mapX, mapY));

                    }
                }
            }
            x += INCREMENT_VALUE_X;
            aux_x++;
        }
        y += INCREMENT_VALUE_Y;
        aux_y++;
    }
    draw_player(cube);
    mlx_put_image_to_window(cube->grafic->mlx,
        cube->grafic->win, cube->grafic->mini_map->img, 0, 0);
}

