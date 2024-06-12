#include "../include/cub3d.h"


void	my_pixel_put(t_image *img, double x, double y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pix_addr)) = color;
}

void    draw_player(t_cube *cube)
{
    int i;
    int j;
    int color;

    color = H_MAGENTA;
    i = 0;
    while (i < INCREMENT_VALUE_X)
    {
        j = 0;
        while (j < INCREMENT_VALUE_Y)
        {
            my_pixel_put(cube->grafic->image_map, (INCREMENT_VALUE_X *
            cube->pj.x) + i, (INCREMENT_VALUE_Y * cube->pj.y) + j, color);
            j++;
        }
        i++;
    }
}

void    print_ch(t_cube *cube, char ch, int x, int y)
{
    int color;
    
    color = H_BG_BLACK;
    if (ch == '1')
        color = H_BG_RED;
    else if (ch == '0')
        color = H_BG_GREENFOSFI;
    else if (ch == 'D')
        color = H_BG_ORANGE;

    my_pixel_put(cube->grafic->image_map, (double)x, (double)y, color);
}

void    mini_map(t_cube *cube)
{

    const int START_POINT_X = 0;
    const int START_POINT_Y = 0;

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
                    print_ch(cube, cube->map[i][j], start_x + iterable[0], start_y + iterable[1]);
                }
            }
            start_x += INCREMENT_VALUE_X;
        }
        /* Increments to the next line */
        start_y += INCREMENT_VALUE_Y;
        start_x = START_POINT_X;
    }

    draw_player(cube);
    // my_pixel_put(cube->grafic->image, START_POINT_X + cube->pj.x, START_POINT_Y + cube->pj.y, H_RED);
    mlx_put_image_to_window(cube->grafic->mlx,
        cube->grafic->win, cube->grafic->image_map->img, 0, 0);
}
