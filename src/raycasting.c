#include "../include/cub3d.h"

/*void    get_vertical_intersection(t_cube *cube, t_ray   *ray)
{

}*/

double    get_horizontal_intersection(t_cube *cube, t_ray   *ray)
{
    double  x_increment;
    double  y_increment;
    double  distance; /* TODO: get distance */

    y_increment = CUBE_HEIGTH;
    x_increment = CUBE_HEIGTH / tan(60);
    // printf("%lf, %lf\n", y_increment, x_increment);

    ray->hor_y = floor(cube->pj.unit_y / CUBE_HEIGTH) * CUBE_HEIGTH - 1;
    ray->hor_x = cube->pj.unit_x + (ray->hor_y - cube->pj.unit_y) / tan(ray->angle);
    ray->hor_y = ray->hor_y / CUBE_HEIGTH;
    ray->hor_x = ray->hor_x / CUBE_HEIGTH;
    while (cube->map[(int)ray->hor_x][(int)ray->hor_y] == '0')
    {
        /* TODO: hay que tener en cuenta hacia donde mira el pj */
        /* down and right, down and left, or up and left */
        /* Calcular los puntos de interseccion rayo cuadrado hasta encontrar un 1 */
        if (ray->angle > M_PI)
            y_increment = CUBE_HEIGTH;
        else
            y_increment = - CUBE_HEIGTH;
        ray->hor_x = ray->hor_x + x_increment;
        ray->hor_y = ray->hor_y + y_increment;
        ray->hor_y = ray->hor_y / CUBE_HEIGTH;
        ray->hor_x = ray->hor_x / CUBE_HEIGTH;
    }
    /* TODO: sacar la distancia del pj hasta la primera pared */
    distance = sqrt((pow(cube->pj.unit_x - (ray->hor_x * 64), 2) +  pow(cube->pj.unit_y - (ray->hor_y * 64), 2)));
    distance = distance * cos(fabs(cube->pj.fov_rd - ray->angle));
    printf("Player: {%lf, %lf} ('%c'), Point: {%lf, %lf} ==> Distance: %lf\n", cube->pj.unit_x, cube->pj.unit_y, cube->map[(int)ray->hor_x][(int)ray->hor_y], ray->hor_x, ray->hor_y, distance);
    return (distance);
}

void    print_wall_h(t_cube *cube, int win_pos, int dis)
{
    int j = CENTER_y;
    int color = H_MAGENTA;
    while (j > dis)
    {
        my_pixel_put(cube->grafic->image, win_pos, j, color);
        j--;
    }
}

void    raycasting(t_cube *cube)
{
    t_ray   ray;
    double  dis_hor;
    double  dis_ver;
    int     i;


    i = WINDOW_WIDTH - 1;
    (void)dis_hor;
    (void)dis_ver;
    /* angulo del primer rayo */
    ray.angle = cube->pj.orientation - (cube->pj.fov_rd / 2);
    /* DEBUGGING: */
    printf("while end %lf\n", cube->pj.orientation + (cube->pj.fov_rd / 2));
    /* DEBUGGING: */
    while (ray.angle < cube->pj.orientation + (cube->pj.fov_rd / 2))
    {
        /* TODO: get the horizontal intersection */
        dis_hor = get_horizontal_intersection(cube, &ray);
        // printf("distancia horizontal %lf\n", dis_hor);
        /* TODO: get the vertical interception */
        /* TODO calculate the distance */
        /* TODO: take the closet distance */
        /* TODO: ver si es mas cercano el lado horizontal o vertical para imprimir columna de pixeles*/
        print_wall_h(cube, i, dis_hor);
        /* Iterar por todos los angulos dentro del FOV del pj*/
        ray.angle = fmod(ray.angle + (cube->pj.fov_rd / WINDOW_WIDTH), 2 * M_PI);
        /* DEBUGGING: printf("ray.angle ---> %lf\n", ray.angle);*/
        i--;
    }
    mlx_put_image_to_window(cube->grafic->mlx,
        cube->grafic->win, cube->grafic->image->img, 0, 0);
}

void    render(t_cube *cube)
{
    raycasting(cube);
    mini_map(cube);
}