#include "../includes/cub3d.h"

int main(void)
{
    void    *mlx;
    void    *window;

    mlx = mlx_init();
    window = mlx_new_window(mlx, 100, 100, "cub3d");
    (void)window;
    mlx_loop(mlx);
    return (0);
}