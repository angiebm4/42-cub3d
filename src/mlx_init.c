#include "../include/cub3d.h"

void    init_textures(t_cube *cube, t_parsed_data *parsed)
{
    int img_width;
    int img_height;
    int i;

    i = 0;
    while (i < TEXTURES_COUNT)
    {
        if (i == DOOR_TEXTURE && cube->grafic->textures[i] == NULL)
        {
            i++;
            continue ;
        }
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

void    get_map_measures(t_cube *cube)
{
    int w;
    int h;

    h = 0;
    while (cube->map[h])
    {
        w = 0;
        while(cube->map[h][w])
        {
            if (w > cube->map_w)
                cube->map_w = w;
            w++;
        }
        if (h > cube->map_h)
                cube->map_h = h;
        h++;
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
    get_map_measures(cube);
}

static void    init_player(t_cube *cube, t_parsed_data *parsed)
{
    int x, y;
    int index;

    x = y = -1;
    index = -1;
    while (PJ_CHARS[++index] && x == -1 && y == -1)
        search_map(parsed->map, PJ_CHARS[index], &x, &y);

    cube->pj.posX = x + 0.5;
    cube->pj.posY = y + 0.5;
    cube->map[y][x] = '0';

    /* TODO: Change the orientation depending of the player char */
    cube->pj.dirX = 0.0;
    cube->pj.dirY = -1.0;

    cube->pj.planeX = 0.66;
    cube->pj.planeY = 0.0;

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

static void	create_image_map(t_cube *cube)
{
	cube->grafic->mini_map->img = mlx_new_image(cube->grafic->mlx, MINIMAP_WIDTH, MINIMAP_HEIGHT);
	if (cube->grafic->mini_map->img == NULL)
		exit(1); /* TODO: malloc error*/
	cube->grafic->mini_map->pix_addr = mlx_get_data_addr(cube->grafic->mini_map->img,
			&cube->grafic->mini_map->bpp,
			&cube->grafic->mini_map->line_len,
			&cube->grafic->mini_map->endian);
}

void	cube_mlx_init(t_cube *cube, t_parsed_data *parsed)
{
    cube->map_h = 0;
    cube->map_w = 0;
    cube->grafic = ft_calloc(1, sizeof(t_mlx));
    if (cube->grafic == NULL)
        exit(1); /* TODO: malloc error*/

    cube->grafic->mlx = mlx_init();
    if (cube->grafic->mlx == NULL)
        exit(1); /* TODO: error  create mlx*/

    init_map(cube, parsed);
    init_textures(cube, parsed);

    cube->grafic->win = mlx_new_window(cube->grafic->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, PROGRAM_NAME);
    if (cube->grafic->win == NULL)
        exit(1); /* TODO: error win create*/

    /* Init the image information */
    /* TODO: Check errors on init */
    cube->grafic->img = mlx_new_image(cube->grafic->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
    cube->grafic->data_addr = mlx_get_data_addr(cube->grafic->img, &cube->grafic->bpp, &cube->grafic->size_line, &cube->grafic->endian);

    cube->grafic->mini_map = ft_calloc(1, sizeof(t_image));
    if (cube->grafic->mini_map == NULL)
        exit(1); /* TODO: malloc error*/
    create_image_map(cube);

    ft_bzero(&cube->pj, sizeof(t_player));
    init_player(cube, parsed);

    ft_bzero(&cube->grafic->raycasting, sizeof(t_raycasting));

    ft_bzero(&cube->grafic->mouse, sizeof(t_mouse));
    cube->grafic->mouse.lastX = -1;
    cube->grafic->mouse.mouse_vision = 1;
    cube->grafic->mouse.fixed = 1;

    destroy_parsed(parsed);
}