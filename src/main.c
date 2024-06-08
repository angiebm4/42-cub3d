#include "../include/cub3d.h"

void    print_data(t_cube *cube)
{
    printf("======== DATA ========\n");
    printf("-> grafic mlx %p\n", cube->grafic->mlx);
    printf("-> grafic win %p\n", cube->grafic->win);
    int i;
    i = 0;
    while (i < 4)
    {
        printf("-> grafic tex %d, %p\n", i, cube->grafic->textures[i]);
        i++;
    }
}

int main(int argc, char *argv[])
{
    t_parsed_data   parsed;

    parse(argc, argv, &parsed);

    t_cube  cube;

    ft_bzero(&cube, sizeof(t_cube));
    cube_mlx_init(&cube, &parsed);
    mini_map(&cube);
    /* DEBUGGING: */
    printf("uwu_2\n");

    /* TODO: 
        fill_data(cube, parsed)
        destroy_parsed(&parsed);
        start_simulation();
    */
    hooking(&cube);
    mlx_loop(cube.grafic->mlx);

    return (0);
}