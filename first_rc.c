#include "../include/cub3d.h"

/* Calcular la distancia */
/* intersecciones horizontales*/
/* intersecciones verticales*/
/* interseccion mas cercana */

/* renderizar segun posicion */

/*
1. Player/viewer’s height ok
, player’s field of view (FOV) ok
, and player’s position. ok
2. Projection plane’s dimension. 320
3. Relationship between player and projection plane. 
*/

/* distancia entre el pj y el plano de proyeccion  
(WINDOW_WEIGTH / 2) / tan(PJ_FOV / 2) = ¿?¿?
WINDOW_WEIGTH colum = PJ_FOV degree 
1 colum = PJ_FOV / WINDOW_WEIGTH degree */

/*
Dimension of the Projection Plane = 320 x 200 units
Center of the Projection Plane = (160,100)
Distance to the Projection Plane = 277 units
Angle between subsequent rays = 60/320 degrees
*/

/*(We will occasionally refer the “angle between subsequent rays” 
as the “angle between subsequent columns.” Later, this angle will 
be used to loop from column to column. The distance between player 
to the projection plane will be used for scaling.)*/

double  distance_pj_wall(t_cube *cube, double p_x, double p_y, double angle )
{
    double distance;

    (void)p_y;
    distance = fabs(cube->pj.x - p_x) / cos(angle);
    distance = distance * cos(60);
    return(distance);
}

void    print_wall_h(t_cube *cube, double x, double y, int win_pos, double angle)
{
    double dis;

    double distance = distance_pj_wall(cube, x, y, angle);
    printf("---> %lf\n", distance);
    dis = 64 / distance;
    printf(">>> %lf\n", dis);
    int j = 0;
    int color = H_MAGENTA;
    while (j < dis)
    {
        mlx_pixel_put(cube->grafic->mlx, cube->grafic->win, (int)win_pos, j, color );
        j++;
    }
}

#include <math.h>

/* horizontales y verticales dos funciones diferentes para cada una */
void    draw_horizontal_walls(t_cube *cube)
{
    int     i;
    double  angle;
    double  aux_point_x;
    double  aux_point_y;

    aux_point_y = 0;
    aux_point_x = 0;
    (void)cube;
    angle = 60;
    i = 0;
    while (i < WINDOW_HEIGTH)
    {
        double ya = -64;
        double xa = 64 / tan(angle);
        //printf("-- %f --\n", xa);
        //printf("-- %f --\n", ya);
        /*If the ray is facing up      
        A.y = rounded_down(Py/64) * (64) - 1;
        If the ray is facing down
        A.y = rounded_down(Py/64) * (64) + 64;*/
        if (cube->pj.orientation > 180)
            aux_point_y = floor(cube->pj.y / 64) * (64) - 1;
        else
            aux_point_y = floor(cube->pj.y / 64) * (64) + 64;
        aux_point_y = floor(aux_point_y / 64);
        aux_point_x = cube->pj.x + ( cube->pj.y - aux_point_y)/tan(angle);
        aux_point_x = floor(aux_point_x / 64);
        //printf(" aux_point_x -- %f --\n", aux_point_x);
        // printf("aux_point_y -- %f --\n", aux_point_y);
        while(cube->map[(int)aux_point_x][(int)aux_point_y] == '0')
        {
            aux_point_y = (aux_point_y + ya) / 64;
            aux_point_x = (aux_point_x + xa) / 64;
            printf(" aux_point_x -- %f --\n", aux_point_x);
            printf("aux_point_y -- %f --\n", aux_point_y);
        }
        if (cube->map[(int)aux_point_x][(int)aux_point_y] == '1')
        {
            print_wall_h(cube, aux_point_x, aux_point_y, i, angle); /* TODO: */
            printf("uwu\n");
        }
        angle += 60/320;
        i++;
    }
}

void    print_wall_v(t_cube *cube, double x, double y, int win_pos, double angle)
{
    double dis;

    double distance = distance_pj_wall(cube, x, y, angle);
    printf("---> %lf\n", distance);
    dis = 64 / distance;
    printf(">>> %lf\n", dis);
    int j = 0;
    int color = H_YELLOW;
    while (j < dis)
    {
        mlx_pixel_put(cube->grafic->mlx, cube->grafic->win, (int)win_pos, j, color );
        j++;
    }
}

void    draw_vertical_walls(t_cube *cube)
{
    int     i;
    double  angle;
    double  aux_point_x;
    double  aux_point_y;

    aux_point_y = 0;
    aux_point_x = 0;
    angle = 30;
    i = 0;
    while (i < WINDOW_HEIGTH)
    {
        double ya = 64 * tan(angle);
        double xa = 64;
        //printf("-- %f --\n", xa);
        //printf("-- %f --\n", ya);
        /*If the ray is facing up      
        A.y = rounded_down(Py/64) * (64) - 1;
        If the ray is facing down
        A.y = rounded_down(Py/64) * (64) + 64;*/
        if (cube->pj.orientation > 90 && cube->pj.orientation < 270)
            aux_point_x = floor(cube->pj.x / 64) * (64) - 1;
        else
            aux_point_x = floor(cube->pj.x / 64) * (64) + 64;
        aux_point_x = floor(aux_point_x / 64);
        aux_point_y = cube->pj.y + ( cube->pj.x - aux_point_x)/tan(angle);
        aux_point_y = floor(aux_point_y / 64);
        //printf(" aux_point_x -- %f --\n", aux_point_x);
        // printf("aux_point_y -- %f --\n", aux_point_y);
        while(cube->map[(int)aux_point_x][(int)aux_point_y] == '0')
        {
            aux_point_x = (aux_point_x + xa) / 64;
            aux_point_y = (aux_point_y + ya) / 64;
            printf(" aux_point_x -- %f --\n", aux_point_x);
            printf("aux_point_y -- %f --\n", aux_point_y);
        }
        if (cube->map[(int)aux_point_x][(int)aux_point_y] == '1')
        {
            print_wall_v(cube, aux_point_x, aux_point_y, i, angle);
            printf("uwu\n");
        }
        angle += 60/320;
        i++;
    }
}

void    draw_walls(t_cube *cube)
{
    (void)cube;
    //draw_horizontal_walls(cube);
    // draw_vertical_walls(cube);
}