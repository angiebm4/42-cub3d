#include "../include/cub3d.h"

void    init_textures(t_cube *cube, t_parsed_data *parsed)
{
    // int img_width;
    // int img_height;
    int i;
    int res;

    i = 0;
    while (i < TEXTURES_COUNT)
    {
        if (i == DOOR_TEXTURE && parsed->textures_name[i] == NULL)
        {
            i++;
            continue ;
        }
        // cube->grafic->textures[i] = 
        //     mlx_xpm_file_to_image(cube->grafic->mlx, parsed->textures_name[i],
        //     &img_width, &img_height);
        res = load_image(parsed->textures_name[i], &cube->grafic->textures[i], cube->grafic, TEXTURE_DIMENSION);
        if (res)
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

void    init_doors(t_cube *cube, t_parsed_data *parsed)
{
    t_list  *it;
    t_list  *node;
    t_door  *door;

    it = parsed->doors;
    while (it)
    {
        door = ft_calloc(1, sizeof(t_door));
        if (!door)
            exit(1);    /* TODO: Check malloc */

        door->x = ((t_door*)it->content)->x;
        door->y = ((t_door*)it->content)->y;
        door->open = ((t_door*)it->content)->open;
        
        node = ft_lstnew(door);
        if (!node)
            exit(1);    /* TODO: Check malloc */

        ft_lstadd_back(&cube->doors, node);
        it = it->next;
    }
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
    init_doors(cube, parsed);


    cube->grafic->win = mlx_new_window(cube->grafic->mlx, WINDOW_WIDTH, WINDOW_HEIGTH, PROGRAM_NAME);
    if (cube->grafic->win == NULL)
        exit(1); /* TODO: error win create*/

    /* Init the image information */
    /* TODO: Check errors on init */
    if (create_image(&cube->grafic->screen, cube->grafic, WINDOW_WIDTH, WINDOW_HEIGTH))
    {
        /* TODO: Error */
        exit(1);
    }

    ft_bzero(&cube->pj, sizeof(t_player));
    init_player(cube, parsed);

    ft_bzero(&cube->grafic->raycasting, sizeof(t_raycasting));

    ft_bzero(&cube->grafic->mouse, sizeof(t_mouse));
    cube->grafic->mouse.lastX = -1;
    cube->grafic->mouse.mouse_vision = 1;
    cube->grafic->mouse.fixed = 0;

    destroy_parsed(parsed);
}