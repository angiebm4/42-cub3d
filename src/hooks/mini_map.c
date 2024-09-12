#include "../include/cub3d.h"

void    print_ch(t_cube *cube, char ch, int x, int y)
{
    int color;
    
    color = H_BG_BLACK;
    if (ch == '1')
        color = H_BG_CYAN;
    else if (ch == '0')
        color = H_BG_WHITE;
    else if (ch == 'D')
        color = H_BG_ORANGE;


    mlx_pixel_put(cube->grafic->mlx, cube->grafic->win, x, y, color);
}

void    mini_map(t_cube *cube)
{

    const int INCREMENT_VALUE_Y = 10;
    const int INCREMENT_VALUE_X = 10;

    const int START_POINT_X = 50;
    const int START_POINT_Y = 50;

    int iterable[2]; // [x, y]


    int i;
    int j;

    int start_x = START_POINT_X;
    int start_y = START_POINT_Y;

    i = -1;
    while (cube->map[++i])
    {
        j = -1;
        /* Print a line of the map */
        while (cube->map[i][++j])
        {
            /* Prints each character */
            iterable[1] = -1;
            while (++iterable[1] < INCREMENT_VALUE_Y)
            {
                iterable[0] = -1;
                while (++iterable[0] < INCREMENT_VALUE_X)
                {
                    // mlx_pixel_put(cube->grafic->mlx, cube->grafic->win, start_x + iterable[0], start_y + iterable[1], H_BG_GREENFOSFI);
                    print_ch(cube, cube->map[i][j], start_x + iterable[0], start_y + iterable[1]);
                }
            }
            start_x += INCREMENT_VALUE_X;
        }
        /* Increments to the next line */
        start_y += INCREMENT_VALUE_Y;
        start_x = START_POINT_X;
    }

}
