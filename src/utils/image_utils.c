#include "../../include/cub3d.h"

static int	get_image_data(t_image *image)
{
	image->data_addr = mlx_get_data_addr(image->img, &image->bpp, &image->size_line, &image->endian);
	return (image->data_addr == NULL);
}

int	create_image(t_image *image, t_mlx *mlx, int width, int heigth)
{
	if (!image)
		return (1);
	
	image->img = mlx_new_image(mlx->mlx, width, heigth);
	if (!image->img)
		return (1);
	
	return (get_image_data(image));
}

int load_image(char *path, t_image *image, t_mlx *mlx, int dim)
{	
	int	width;
	int	height;

	if (!path || !image || !mlx)
		return (1);
	
	printf("=> {%s} | %p\n", path, mlx->mlx);
	image->img = mlx_xpm_file_to_image(mlx->mlx, path, &width, &height);
	printf("[%d | %d]\n", width, height);
	if (!image->img || width != dim || height != dim)
		return (1);
	
	return (get_image_data(image));
}

char *get_pixel(t_image *image, int x, int y)
{
	return (image->data_addr + (y * image->size_line + x * (image->bpp / 8)));
}
