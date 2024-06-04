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

    /* TODO: 
        t_cube          cube;
        fill_data(cube, parsed)
        destroy_parsed(&parsed);
        start_simulation();
    */

    destroy_parsed(&parsed);

    return (0);
}