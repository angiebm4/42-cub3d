#include "../include/cub3d.h"


void	render(t_cube *cube)
{
	int x = -1;

	/* TODO: Check if the variables should be saved on the struct,
			 to use it on another iterations
	*/
	double	planeX = 0, planeY = 0.66;

	while (++x < WINDOW_WIDTH)
	{
		/* Get the current camera position and the rays direction */
		double	cameraX = ((2 * x) / (double)WINDOW_WIDTH) - 1;
		double	rayDirX = cube->pj.dirX + planeX * cameraX;
		double	rayDirY = cube->pj.dirY + planeY * cameraX;

		/* Player coordenates */
		int	mapX = cube->pj.posX;
		int	mapY = cube->pj.posY;

		/* Length of the ray */
		double	deltaX = (rayDirX == 0) ? 1e30 : abs((int)(1 / rayDirX));
		double	deltaY = (rayDirY == 0) ? 1e30 : abs((int)(1 / rayDirY));

		
		double	sideDistX, sideDistY;	/* Get the side of the rays */
		int		stepX, stepY;			/* Direction into where step */

		/* Get the data about the rays */
		if (rayDirX < 0) {
			stepX = -1;
			sideDistX = (cube->pj.posX - mapX) * deltaX;
		} else {
			stepX = 1;
        	sideDistX = (mapX + 1.0 - cube->pj.posX) * deltaX;
		}

		if (rayDirY < 0) {
			stepY = -1;
			sideDistY = (cube->pj.posY - mapY) * deltaY;
		} else {
			stepX = 1;
        	sideDistX = (mapY + 1.0 - cube->pj.posY) * deltaY;
		}
		
		/* Get the hit points */
		int side = 0;
		int hit = 0;
		while (!hit) {
			if (sideDistX < sideDistY) {
				sideDistX += deltaX;
				mapX += stepX;
				side = 0;
			} else {
				sideDistY += deltaY;
				mapY += stepY;
				side = 1;
			}

			if (cube->map[mapY][mapX] > 0)
				hit = 1;
		}

		/* Get the perpendicular distance between the player and the point*/
		int perpWallDist;
		if (side == 0)
			perpWallDist = (sideDistX - deltaX);
		else
			perpWallDist = (sideDistY - deltaY);
		(void)perpWallDist;

		/* Height of the line */
		int lineHeight = (int)(WINDOW_HEIGTH / perpWallDist);

		/* Calculates pixels */
		int startPixel = -lineHeight/2 + WINDOW_HEIGTH/2;
		if (startPixel < 0)
			startPixel = 0;
		
		int endPixel = lineHeight/2 + WINDOW_HEIGTH/2;
		if (endPixel >= WINDOW_HEIGTH)
			endPixel = WINDOW_HEIGTH - 1;

		int color;
		if (side == 1)
			color = H_CYAN;
		else
			color = H_GREEN;
		
		while (startPixel < endPixel) {
			mlx_pixel_put(cube->grafic->mlx, cube->grafic->win, x, startPixel, color);
			startPixel++;
		}

	}
	
}	