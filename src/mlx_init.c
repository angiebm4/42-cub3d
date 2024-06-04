#include "../include/cub3d.h"

int end_program(t_cube *cube)
{
    if (cube->grafic->win)
        mlx_destroy_window(cube->grafic->mlx, cube->grafic->win);
    if (cube->map)
        ft_free_split(cube->map);
    exit(1);
}

int key_hooks(int keycode, t_cube *cube)
{
    /* DEBUGGING: */
    printf("tecla %d\n", keycode);
    if (keycode == ESC)
        end_program(cube);
    return(1);
}

void    hooking(t_cube *cube)
{
    mlx_hook(cube->grafic->win, ON_DESTROY, 0, &end_program, cube);
    mlx_key_hook(cube->grafic->win, key_hooks, cube);
    /* DEBUGGING: */
    printf("uwu\n");
}

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

void	cube_mlx_init(t_cube *cube, t_parsed_data *parsed)
{
    (void)parsed;
    cube->grafic = ft_calloc(1, sizeof(t_mlx));
    if (cube->grafic == NULL)
        exit(1); /* TODO: malloc error*/

    cube->grafic->mlx = mlx_init();
    if (cube->grafic->mlx == NULL)
        exit(1); /* TODO: error  create mlx*/

    init_map(cube, parsed);
    init_textures(cube, parsed);

    cube->grafic->win = mlx_new_window(cube->grafic->mlx, WINDOW_HEIGTH, WINDOW_WEIGTH, PROGRAM_NAME);
    if (cube->grafic->win == NULL)
        exit(1); /* TODO: error win create*/
        
    destroy_parsed(parsed);
    hooking(cube);
    mlx_loop(cube->grafic->mlx);
    
}