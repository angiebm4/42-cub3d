#include "../include/cub3d.h"

double  distance_pj_wall(t_cube *cube, double p_x, double angle)
{
    double  distance;
    double  real_distance;

    distance = fabs(cube->pj.x - p_x) / cos(angle);
    real_distance = distance * cos(angle);
    printf("real distance --> %fl\n", real_distance);
    return(real_distance);
}

void    print_wall(t_cube *cube, double distance, int win_pos, int color)
{
    int i;

    i = 0;
    while(i < distance)
    {
        mlx_pixel_put(cube->grafic->mlx, cube->grafic->win, win_pos, CENTER_y - i, color);
        i++;
    }
}

void    draw_horizontal_walls(t_cube *cube)
{
    int i;
    double auxp_x;
    double auxp_y;
    double angle;
    double Xa;
    double Ya;

    /* TODO: funcion de sumar angulos de 0 a 360 */
    angle = cube->pj.orientation - (PJ_FOV / 2);
    printf("angle --- %lf\n", angle);
    i = 0;
    while (i < WINDOW_WIDTH)
    {
        
        Xa = CUBE_HEIGTH / tan(angle);
        printf("xa --- %lf\n", Xa);
        if (angle < 360 && angle > 180)
        {
            auxp_y = floor(cube->pj.unit_y / 64) * (64) + 64;
            Ya = CUBE_HEIGTH;
        }
        else
        {
            auxp_y = floor(cube->pj.unit_y / 64) * (64) - 1;
            Ya = -CUBE_HEIGTH;
        }
        auxp_x = cube->pj.unit_x + (cube->pj.unit_y - auxp_y) / tan(angle);
        auxp_y = floor(auxp_y / 64);
        printf("%saux Y ---> %lf%s\n",RED, auxp_y, CLEAR);
        auxp_x = floor(auxp_x / 64);
        printf("%saux x ---> %lf%s\n",RED, auxp_x, CLEAR);
        while (cube->map[(int)auxp_y][(int)auxp_x] == '0')
        {
            auxp_x = (auxp_x + Xa) / CUBE_HEIGTH;
            auxp_y = (auxp_y + Ya) / CUBE_HEIGTH;
        }
        print_wall(cube ,distance_pj_wall(cube, auxp_x, angle), i, H_MAGENTA);
        /* TODO: funcion de sumar angulos de 0 a 360 */
        angle += 60 / 320;
        printf("<<< %lf >>>\n", angle);
        i++;
    }
}

void    draw_walls(t_cube *cube)
{
    draw_horizontal_walls(cube);
    // draw_vertical_walls(cube);
}
