#include "../../include/cub3d.h"

static void	clean_images(t_image *images, size_t size, void *mlx)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		mlx_destroy_image(mlx, images[i].img);
		i++;
	}
}

static void	screen_destroy(t_cube *cube)
{
	mlx_loop_end(cube->grafic->mlx);
	mlx_destroy_image(cube->grafic->mlx, cube->grafic->screen.img);
	clean_images(cube->grafic->textures, TEXTURES_COUNT, cube->grafic->mlx);
	clean_images(cube->grafic->compass, COMPASS_TEXTURES, cube->grafic->mlx);
	mlx_destroy_window(cube->grafic->mlx, cube->grafic->win);
	mlx_destroy_display(cube->grafic->mlx);
	free(cube->grafic->mlx);
	free(cube->grafic);
}

void	cube_destroy(t_cube *cube)
{
	ft_free_split(cube->map);
	ft_lstclear(&cube->doors, free);
	screen_destroy(cube);
}
