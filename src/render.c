#include "../include/cub3d.h"


// void	render(t_cube *cube)
// {
// 	int x = -1;

// 	/* TODO: Check if the variables should be saved on the struct,
// 			 to use it on another iterations
// 	*/
// 	double	planeX = 0, planeY = 0.66;

// 	int w = 24, h = 24;

// 	while (++x < w)
// 	{
// 		/* Get the current camera position and the rays direction */
// 		double	cameraX = ((2 * x) / (double)w) - 1;
// 		double	rayDirX = cube->pj.dirX + planeX * cameraX;
// 		double	rayDirY = cube->pj.dirY + planeY * cameraX;

// 		/* Player coordenates */
// 		int	mapX = (int)cube->pj.posX;
// 		int	mapY = (int)cube->pj.posY;

// 		/* Length of the ray */
// 		printf("=> [RayDirX: %lf, RayDirY: %lf]\n", rayDirX, rayDirY);
// 		double	deltaX = (rayDirX == 0) ? 1e30 : fabs((1 / rayDirX));
// 		double	deltaY = (rayDirY == 0) ? 1e30 : fabs((1 / rayDirY));

		
// 		double	sideDistX, sideDistY;	/* Get the side of the rays */
// 		int		stepX, stepY;			/* Direction into where step */

// 		/* Get the data about the rays */
// 		if (rayDirX < 0) {
// 			stepX = -1;
// 			sideDistX = (cube->pj.posX - mapX) * deltaX;
// 		} else {
// 			stepX = 1;
//         	sideDistX = (mapX + 1.0 - cube->pj.posX) * deltaX;
// 		}

// 		if (rayDirY < 0) {
// 			stepY = -1;
// 			sideDistY = (cube->pj.posY - mapY) * deltaY;
// 		} else {
// 			stepX = 1;
//         	sideDistX = (mapY + 1.0 - cube->pj.posY) * deltaY;
// 		}
		
// 		/* Get the hit points */
// 		int side = 0;
// 		int hit = 0;
// 		while (hit == 0) {
// 			if (sideDistX < sideDistY) {
// 				sideDistX += deltaX;
// 				mapX += stepX;
// 				side = 0;
// 			} else {
// 				sideDistY += deltaY;
// 				mapY += stepY;
// 				side = 1;
// 			}

// 			if (cube->map[mapY][mapX] > 0)
// 				hit = 1;
// 		}

// 		/* Get the perpendicular distance between the player and the point*/
// 		double	perpWallDist;
// 		if (side == 0)
// 			// perpWallDist = (sideDistX - deltaX);
// 			perpWallDist =(mapX - cube->pj.posX + (1 - stepX) / 2) / rayDirX;
// 		else
// 			// perpWallDist = (sideDistY - deltaY);
// 			perpWallDist = (mapY - cube->pj.posY + (1 - stepY) / 2) / rayDirY;


// 		/* Height of the line */
// 		int lineHeight = (int)(h / perpWallDist);

// 		/* Calculates pixels */
// 		int startPixel = -lineHeight/2 + h/2;
// 		if (startPixel < 0)
// 			startPixel = 0;
		
// 		int endPixel = lineHeight/2 + h/2;
// 		if (endPixel >= h)
// 			endPixel = h - 1;

// 		int color;
// 		if (side == 1)
// 			color = H_CYAN;
// 		else
// 			color = H_GREEN;
		
// 		while (startPixel < endPixel) {
// 			mlx_pixel_put(cube->grafic->mlx, cube->grafic->win, x, startPixel, color);
// 			startPixel++;
// 		}

// 	}
	
// }

void render(t_cube *cube)
{
	int w = 640; // Ancho de la ventana
	int h = 480; // Alto de la ventana

	double planeX = 0;
	double planeY = 0.66;

	for (int x = 0; x < w; x++)
	{
		double cameraX = 2 * x / (double)w - 1;
		double rayDirX = cube->pj.dirX + planeX * cameraX;
		double rayDirY = cube->pj.dirY + planeY * cameraX;

		int mapX = (int)cube->pj.posX;
		int mapY = (int)cube->pj.posY;

		double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
		double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

		double sideDistX, sideDistY;
		int stepX, stepY;

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

		int hit = 0;
		int side;

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

			if (cube->map[mapY][mapX] > 0) hit = 1;
		}

		double perpWallDist;
		if (side == 0)
			perpWallDist = (mapX - cube->pj.posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - cube->pj.posY + (1 - stepY) / 2) / rayDirY;

		int lineHeight = (int)(h / perpWallDist);

		long startPixel = lineHeight / 2 + h / 2;
		if (startPixel < 0) startPixel = 0;
		long endPixel = -lineHeight / 2 + h / 2;
		if (endPixel >= h) endPixel = h - 1;

		int color;
		if (side == 1)
			color = H_CYAN;
		else
			color = H_GREEN;
		for (int y = startPixel; y <= endPixel; y++)
			mlx_pixel_put(cube->grafic->mlx, cube->grafic->win, x, y, color);
	}
}
