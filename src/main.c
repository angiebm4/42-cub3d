#include "../include/cub3d.h"

int	main(int argc, char *argv[])
{
	t_cube			cube;
	t_parsed_data	parsed;

	ft_bzero(&cube, sizeof(t_cube));
	parse(argc, argv, &parsed);
	if (DEBUG)
	{
		destroy_parsed(&parsed);
		return (0);
	}
	cube_mlx_init(&cube, &parsed);
	hooking(&cube);
	mlx_loop(cube.grafic->mlx);
	return (0);
}
