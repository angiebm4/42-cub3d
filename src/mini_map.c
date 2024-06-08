#include "../include/cub3d.h"

void    save_player_info(t_cube *cube)
{
    int i;
    int aux_x;
    int aux_y;

    i = 0;
    aux_x = 0;
    aux_y = 0;
    while (i < 4)
    {
        if (search_map(cube->map, PJ_CHARS[i], &aux_x, &aux_y) == 1)
        {
            cube->pj->x = (double)aux_x;
            cube->pj->y = (double)aux_y;
            // printf("%lf\n", cube->pj->x);
            // printf("%lf\n", cube->pj->y);
            if (i == NORTH_TEXTURE)
                cube->pj->orientation = 90;
            else if (i == SOUTH_TEXTURE)
                cube->pj->orientation = 270;
            else if (i == WEST_TEXTURE)
                cube->pj->orientation = 180;
            else if (i == EAST_TEXTURE)
                cube->pj->orientation = 0;
            break ;
        }
        i++;
    }
}
/*
static void	my_pixel_put(t_image *img, double x, double y, int color)
{
	int	offset;

	offset = (img->line_len * y) + (x * (img->bpp / 8));
	*((unsigned int *)(offset + img->pix_addr)) = color;
}

void    draw_player(t_cube *cube)
{
    int color;

    color = H_YELLOW;
    my_pixel_put(cube->grafic->image, cube->pj->x, cube->pj->y, color);
}*/

/*void    draw_map(t_cube *cube)
{

}*/

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


    mlx_pixel_put(cube->grafic->mlx, cube->grafic->win, x, y, color);
}

void    mini_map(t_cube *cube)
{
    // draw_map(cube); 
    // draw_player(cube); /* TODO: reset color */
    // mlx_put_image_to_window(cube->grafic->mlx,
    //     cube->grafic->win, cube->grafic->image->img, 0, 0);

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
