#include "../include/cub3d.h"

int main(int argc, char *argv[])
{
    t_parsed_data   parsed;

    parse(argc, argv, &parsed);

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