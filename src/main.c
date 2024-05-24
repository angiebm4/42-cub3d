#include "../include/cub3d.h"

int error(int msg)
{
    if (msg == ERROR_INVALID_ARGS)
        ft_printf("%sINVALID ARGS, INSERT A MAP: .cub\n%s", C_ORANGE, CLEAR);
    else if (msg == ERROR_OPEN)
        ft_printf("%sOPEN ERROR\n%s", C_ORANGE, CLEAR);
    else if (msg == ERROR_MALLOC)
        ft_printf("%sMALLOC ERROR\n%s", C_ORANGE, CLEAR);
    else if (msg == ERROR_FILE_CONTENT)
        ft_printf("%sINVALID FILE CONTENT\n%s", C_ORANGE, CLEAR);
    else if (msg == ERROR_MLX_TEX_CREATE)
        ft_printf("%sTEXTURE CREATE FAIL MLX FUNCTION\n%s", C_ORANGE, CLEAR);
    else if (msg == ERROR_MLX_INIT)
        ft_printf("%sINIT FAIL MLX FUNCTION\n%s", C_ORANGE, CLEAR);
    return(1);
}

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
    t_cube  cube;

    if (argc != 2)
        return(error(ERROR_INVALID_ARGS));
    if (init_data(&cube, argv[1]) != 0)
        return(1);
    print_data(&cube);
    /*void    *mlx;
    void    *window;

    mlx = mlx_init();
    window = mlx_new_window(mlx, 100, 100, "cub3d");
    (void)window;
    mlx_loop(mlx);*/
    return (0);
}