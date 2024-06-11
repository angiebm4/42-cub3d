#include "../include/cub3d.h"

void    get_vertical_intersection(t_cube *cube, t_ray   *ray)
{

}

double    get_horizontal_intersection(t_cube *cube, t_ray   *ray)
{
    double  x_increment;
    double  y_increment;
    double  distance; /* TODO: get distance */

    while ()
    {
        /* TODO: hay que tener en cuenta hacia donde mira el pj */
        /* down and right, down and left, or up and left */
        /* Calcular los puntos de interseccion rayo cuadrado hasta encontrar un 1 */
        ray->hor_y = (cube->pj.unit_y / CUBE_HEIGTH) * CUBE_HEIGTH;
        ray->hor_x = cube->pj.unit_x + (ray->hor_y - cube->pj.unit_y) / tan(ray->angle);
        y_increment = CUBE_HEIGTH;
        x_increment = CUBE_HEIGTH / tan(ray->angle);

    }
    /* TODO: sacar la distancia del pj hasta la primera pared */
    return (distance);
}
void    raycasting(t_cube *cube)
{
    t_ray   ray;
    double  dis_hor;
    double  dis_ver;


    /* angulo del primer rayo */
    ray.angle = cube->pj.orientation - (cube->pj.fov_rd / 2);
    /* DEBUGGING: */
    printf("while end %lf\n", cube->pj.orientation + (cube->pj.fov_rd / 2));
    /* DEBUGGING: */
    while (ray.angle < cube->pj.orientation + (cube->pj.fov_rd / 2))
    {
        /* TODO: get the horizontal intersection */
        dis_hor = get_horizontal_intersection(cube, &ray);
        /* TODO: get the vertical interception */
        /* TODO calculate the distance */
        /* TODO: take the closet distance */
        /* TODO: ver si es mas cercano el lado horizontal o vertical para imprimir columna de pixeles*/

        /* Iterar por todos los angulos dentro del FOV del pj*/
        ray.angle = fmod(ray.angle + (cube->pj.fov_rd / WINDOW_WIDTH), 2 * M_PI);
        /* DEBUGGING: printf("ray.angle ---> %lf\n", ray.angle);*/
    }
}

void    render(t_cube *cube)
{
    mini_map(cube);
    raycasting(cube);
}