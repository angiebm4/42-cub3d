#include "../include/cub3d.h"

void    init_textures(t_cube *cube, t_parsed_data *parsed)
{
    int img_width;
    int img_height;
    int i;

    i = 0;
    while (i < TEXTURES_COUNT)
    {
        cube->grafic->textures[i] = 
            mlx_xpm_file_to_image(cube->grafic->mlx, parsed->textures_name[i],
            &img_width, &img_height);
        if (cube->grafic->textures[i] == NULL)
        {
            ft_printf("%sINVALID TEXTURE%s\n", RED, CLEAR);
            destroy_parsed(parsed);
            end_program(cube);
        }
        i++;
    }
    i = 0;
    while (i < PIXELS_COUNT)
    {
        pixel_copy(&cube->grafic->default_pixels[i], &parsed->default_pixels[i]);
        i++;
    }
}

void    init_map(t_cube *cube, t_parsed_data *parsed)
{
    int i;

    cube->map = malloc(sizeof(char*) * (map_length(parsed->map) + 1));
    if (cube->map == NULL)
        exit(1); /* TODO: exit malloc error*/

    i = 0;
    while (parsed->map[i])
    {
        cube->map[i] = ft_strdup(parsed->map[i]);
        if (cube->map[i] == NULL)
            exit (1); /* TODO: malloc exit */
        i++;
    }
    cube->map[i] = NULL;
}

static void    init_player(t_cube *cube, t_parsed_data *parsed)
{
    int x, y;
    int index;

    x = y = -1;
    index = -1;
    while (PJ_CHARS[++index] && x != -1 && y != -1)
        search_map(parsed->map, PJ_CHARS[index], &x, &y);

    cube->pj.posX = x;
    cube->pj.posX = y;

    /* TODO: Change the orientation depending of the player char */
    cube->pj.dirX = -1;
    cube->pj.dirX = 0;

    /*switch (cube->map[y][x])
    {
        case 'N':
            cube->pj.orientation = 90;
            break ;
        case 'S':
            cube->pj.orientation = 270;
            break ;
        case 'E':
            cube->pj.orientation = 0;
            break ;
        default: //case 'W':
            cube->pj.orientation = 180;
            break ;
    }*/
}

void	cube_mlx_init(t_cube *cube, t_parsed_data *parsed)
{

    cube->grafic = ft_calloc(1, sizeof(t_mlx));
    if (cube->grafic == NULL)
        exit(1); /* TODO: malloc error*/

    cube->grafic->mlx = mlx_init();
    if (cube->grafic->mlx == NULL)
        exit(1); /* TODO: error  create mlx*/

    init_map(cube, parsed);
    init_textures(cube, parsed);

    cube->grafic->win = mlx_new_window(cube->grafic->mlx, WINDOW_HEIGTH, WINDOW_WIDTH, PROGRAM_NAME);
    if (cube->grafic->win == NULL)
        exit(1); /* TODO: error win create*/

    ft_bzero(&cube->pj, sizeof(t_player));
    init_player(cube, parsed);

    destroy_parsed(parsed);
}