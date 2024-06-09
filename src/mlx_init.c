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

static void	create_image(t_cube *cube)
{
	cube->grafic->image->img = mlx_new_image(cube->grafic->mlx, 50, 50);
	if (cube->grafic->image->img == NULL)
		exit(1); /* TODO: malloc error*/
	cube->grafic->image->pix_addr = mlx_get_data_addr(cube->grafic->image->img,
			&cube->grafic->image->bpp,
			&cube->grafic->image->line_len,
			&cube->grafic->image->endian);
}

void    save_player_info(t_cube *cube)
{
    int i;
    int aux_x;
    int aux_y;

    i = 0;
    aux_x = 0;
    aux_y = 0;
    while (i < 4)
    {
        if (search_map(cube->map, PJ_CHARS[i], &aux_x, &aux_y) == 1)
        {
            cube->pj.x = (double)aux_x;
            cube->pj.y = (double)aux_y;
            /* DEBBUGING: */
            printf("%lf\n", cube->pj.x);
            printf("%lf\n", cube->pj.y);
            /* DEBBUGUNG: */
            if (i == NORTH_TEXTURE)
                cube->pj.orientation = 90;
            else if (i == SOUTH_TEXTURE)
                cube->pj.orientation = 270;
            else if (i == WEST_TEXTURE)
                cube->pj.orientation = 180;
            else if (i == EAST_TEXTURE)
                cube->pj.orientation = 0;
            break ;
        }
        i++;
    }
    cube->map[aux_y][aux_x] = '0';
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

void	cube_mlx_init(t_cube *cube, t_parsed_data *parsed)
{

    cube->grafic = ft_calloc(1, sizeof(t_mlx));
    if (cube->grafic == NULL)
        exit(1); /* TODO: malloc error*/

    cube->grafic->mlx = mlx_init();
    if (cube->grafic->mlx == NULL)
        exit(1); /* TODO: error  create mlx*/

    cube->grafic->image = ft_calloc(1, sizeof(t_image));
    if (cube->grafic->image == NULL)
        exit(1); /* TODO: malloc error*/

    init_map(cube, parsed);
    init_textures(cube, parsed);

    cube->grafic->win = mlx_new_window(cube->grafic->mlx, WINDOW_WEIGTH, WINDOW_HEIGTH, PROGRAM_NAME);
    if (cube->grafic->win == NULL)
        exit(1); /* TODO: error win create*/

    ft_bzero(&cube->pj, sizeof(t_player));
    save_player_info(cube);
    create_image(cube);
    destroy_parsed(parsed);
}