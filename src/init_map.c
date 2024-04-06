#include "../includes/cub3d.h"

void    check_map(t_cube *cube)
{
    if ()
}

int init_textures(t_cube *cube, int file)
{
    char *line;
    
    line = get_next_line(file);
    /* mlx_xpm_file_to_image */
}

int    init_data(t_cube *cube, char *fd)
{
    int file;

    ft_bzero(cube, sizeof(t_cube));

    file = open(fd, O_WRONLY);
    if (file < 0)
        return(error(ERROR_OPEN));

    cube->grafic = ft_calloc(sizeof(t_mlx));
    if (cube->grafic == NULL)
        return(error(ERROR_MALLOC));
    check_map(cube);
    return (0);
}