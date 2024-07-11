#include "../include/cub3d.h"

int main(int argc, char *argv[])
{
    /* Parse the file data */
    t_parsed_data   parsed;
    parse(argc, argv, &parsed);

    if (DEBUG)
    {
        destroy_parsed(&parsed);
        return (0);
    }

    /* Fill the main struct and run the program */
    t_cube  cube;
    ft_bzero(&cube, sizeof(t_cube));
    cube_mlx_init(&cube, &parsed);
    // mini_map(&cube);

    /* TODO: 
        fill_data(cube, parsed)
        destroy_parsed(&parsed);
        start_simulation();
    */
    hooking(&cube);
    mlx_loop(cube.grafic->mlx);

    return (0);
}