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

static void	create_image(t_cube *cube)
{
	cube->grafic->image->img = mlx_new_image(cube->grafic->mlx, WINDOW_WEIGTH, WINDOW_HEIGTH);
	if (cube->grafic->image->img == NULL)
		exit(1); /* TODO: malloc error*/
	cube->grafic->image->pix_addr = mlx_get_data_addr(cube->grafic->image->img,
			&cube->grafic->image->bpp,
			&cube->grafic->image->line_len,
			&cube->grafic->image->endian);
}

void	cube_mlx_init(t_cube *cube, t_parsed_data *parsed)
{
    (void)parsed;
    cube->grafic = ft_calloc(1, sizeof(t_mlx));
    if (cube->grafic == NULL)
        exit(1); /* TODO: malloc error*/

    cube->grafic->image = ft_calloc(1, sizeof(t_image));
    if (cube->grafic->image == NULL)
        exit(1); /* TODO: malloc error*/

    cube->pj = ft_calloc(1, sizeof(t_mlx));
    if (cube->pj == NULL)
        exit(1); /* TODO: malloc error*/

    cube->grafic->mlx = mlx_init();
    if (cube->grafic->mlx == NULL)
        exit(1); /* TODO: error  create mlx*/

    init_map(cube, parsed);
    init_textures(cube, parsed);

    cube->grafic->win = mlx_new_window(cube->grafic->mlx, WINDOW_HEIGTH, WINDOW_WEIGTH, PROGRAM_NAME);
    if (cube->grafic->win == NULL)
        exit(1); /* TODO: error win create*/
        
    create_image(cube);
    save_player_info(cube);

    destroy_parsed(parsed);
}