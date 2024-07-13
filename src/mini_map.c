#include "../include/cub3d.h"


void	my_pixel_put(t_image *img, double x, double y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pix_addr)) = color;
}


void    draw_player(t_cube *cube)
{
    /* TODO: ta mal */
    my_pixel_put(cube->grafic->mini_map, MINIMAP_WIDTH / 2, MINIMAP_HEIGHT / 2, H_ORANGE);

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

void    mini_map(t_cube *cube)
{
    /* TODO: borrar contenido de imagen para volver a escribir*/
    int start_x = cube->pj.posX - cube->map_w / 2;
    int start_y = cube->pj.posY - cube->map_h / 2;

    printf("%d\n", start_x);
    printf("%d\n", start_y);

    
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
