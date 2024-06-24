#include "../include/cub3d.h"


void	draw_pixel(int x, int y, int color, t_cube *cube) {
    if (x >= 0 && x < WINDOW_WIDTH && y >= 0 && y < WINDOW_HEIGTH) {
        char *pixel = cube->grafic->data_addr + (y * cube->grafic->size_line + x * (cube->grafic->bpp / 8));
        *(unsigned int*)pixel = color;
    }
}

void render(t_cube *cube)
{
	for (int x = 0; x < WINDOW_WIDTH; x++)
	{
		double cameraX = 2 * x / (double)WINDOW_WIDTH - 1;
		double rayDirX = cube->pj.dirX + cube->pj.planeX * cameraX;
		double rayDirY = cube->pj.dirY + cube->pj.planeY * cameraX;

		int mapX = (int)cube->pj.posX;
		int mapY = (int)cube->pj.posY;

		double sideDistX, sideDistY;

		double deltaDistX = fabs(1 / rayDirX); //(rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = fabs(1 / rayDirY); //(rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		double perpWallDist;

		int stepX, stepY;
		int hit = 0, side;

		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (cube->pj.posX - mapX) * deltaDistX;
		} else {
			stepX = 1;
			sideDistX = (mapX + 1.0 - cube->pj.posX) * deltaDistX;
		}

		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (cube->pj.posY - mapY) * deltaDistY;
		} else {
			stepY = 1;
			sideDistY = (mapY + 1.0 - cube->pj.posY) * deltaDistY;
		}

		while (hit == 0) {
			if (sideDistX < sideDistY) {
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			if (cube->map[mapY][mapX] > '0')
				hit = 1;
		}
		if (side == 0)
			perpWallDist = (mapX - cube->pj.posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - cube->pj.posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(WINDOW_HEIGTH / perpWallDist);
		
		int drawStart = -lineHeight / 2 + WINDOW_HEIGTH / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + WINDOW_HEIGTH / 2;
		if (drawEnd >= WINDOW_HEIGTH) drawEnd = WINDOW_HEIGTH - 1;

        int color = 0xFFFF00;	/* Yellow */

        if(side == 1) color = color / 2;	/* Green */

		printf("%d - %d\n", drawStart, drawEnd);
        for(int y = drawStart; y <= drawEnd; y++)
            draw_pixel(x, y, color, cube);
	}
	mlx_put_image_to_window(cube->grafic->mlx, cube->grafic->win, cube->grafic->img, 0, 0);
	mlx_do_sync(cube->grafic->mlx); /* It is used to be faster */
}
