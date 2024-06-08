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
            /* DEBBUGING: */
            printf("%lf\n", cube->pj->x);
            printf("%lf\n", cube->pj->y);
            /* DEBBUGUNG: */
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
}

/*void    draw_map(t_cube *cube)
{

}*/

void    mini_map(t_cube *cube)
{
    // draw_map(cube); 
    draw_player(cube); /* TODO: reset color */
    mlx_put_image_to_window(cube->grafic->mlx,
        cube->grafic->win, cube->grafic->image->img, 0, 0);
}
