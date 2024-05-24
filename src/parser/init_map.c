#include "../include/cub3d.h"

/*void    check_map(t_cube *cube)
{
    if ()
}*/

int which_texture(char *line)
{
    int nb_tex;

    nb_tex = 0;
    if (ft_strlen(line) < 3)
        return (-1);
    if (!ft_strncmp(line, "NO ", 3))
        nb_tex = NORTH_TEXTURE;
    else if (!ft_strncmp(line, "SO ", 3))
        nb_tex = SOUTH_TEXTURE;
    else if (!ft_strncmp(line, "WE ", 3))
        nb_tex = WEST_TEXTURE;
    else if (!ft_strncmp(line, "EA ", 3))
        nb_tex = EAST_TEXTURE;
    else
        nb_tex = -1;
    return(nb_tex);
}

int save_map(t_cube *cube, int file)
{

}

int save_rgv(char *line, t_cube *cube)

int init_textures(t_cube *cube, int file)
{
    char    *line;
    int     flag;
    int     tex;
    char    *file_name;
    int     status;
    
    flag = 0;
    status = 0;
    line = get_next_line(file);
    while(line && flag < 4)
    {
        if (!ft_strcmp(line, "\n"))
        {
            free(line);
            line = get_next_line(file);
            if (line == NULL)
                return(error(ERROR_FILE_CONTENT));
        }
        tex = which_texture(line);
        if (tex < 0 || tex > 4)
            return(error(ERROR_FILE_CONTENT));
        if (cube->grafic->textures[tex] != NULL)
            return(error(ERROR_FILE_CONTENT));
        file_name = ft_strdup(&line[3]);
        if (file_name == NULL)
            return(error(ERROR_MALLOC));
        cube->grafic->textures[tex] = mlx_xpm_file_to_image(cube->grafic->mlx, file_name, &status, &status); /* TODO: el tamaño de la textura¿?¿?*/
        if (cube->grafic->textures[tex] == NULL)
            return(error(ERROR_MLX_TEX_CREATE));
        flag++;
        free(line);
        free(file_name);
        line = get_next_line(file);
    }
    while(flag < 6)
    {
        if (!ft_strcmp(line, "\n"))
        {
            free(line);
            line = get_next_line(file);
            if (line == NULL)
                return(error(ERROR_FILE_CONTENT));
        }
        if (!ft_strncmp(line, "C ", 2))
        {
            save_rgv(&line[2], cube)
            flag++;
        }
    }

    return (0);
}

int    init_data(t_cube *cube, char *fd)
{
    int file;

    ft_bzero(cube, sizeof(t_cube));

    file = open(fd, O_RDONLY);
    if (file < 0)
        return(error(ERROR_OPEN));

    cube->grafic = ft_calloc(1, sizeof(t_mlx));
    if (cube->grafic == NULL)
        return(error(ERROR_MALLOC));
    cube->grafic->mlx = mlx_init();
    if (cube->grafic->mlx == NULL)
        return(error(ERROR_MLX_INIT));
    init_textures(cube, file);
    save_map(cube, file);    
    // check_map(cube);
    return (0);
}
