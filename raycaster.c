#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mlx/mlx.h"

// Definición de las dimensiones del mapa y la pantalla
#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

// Estructura para la información del jugador
typedef struct s_player {
    double posX, posY;    // posición del jugador
    double dirX, dirY;    // dirección del jugador
    double planeX, planeY; // plano de la cámara
} t_player;

// Estructura para la información de la ventana
typedef struct s_mlx {
    void *mlx;
    void *win;
    void *img;
    char *data_addr;
    int bpp;
    int size_line;
    int endian;
} t_mlx;

// Mapa del mundo (1: muro, 0: vacío)
int worldMap[mapHeight][mapWidth] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

// Variables globales para jugador y mlx
t_player player = {22.0, 12.0, -1.0, 0.0, 0.0, 0.66};
t_mlx mlx;

// Función para dibujar un píxel en la imagen
void draw_pixel(int x, int y, int color) {
    if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
        char *pixel = mlx.data_addr + (y * mlx.size_line + x * (mlx.bpp / 8));
        *(unsigned int*)pixel = color;
    }
}

// Función de renderizado
void render() {
    for(int x = 0; x < screenWidth; x++) {
        double cameraX = 2 * x / (double)screenWidth - 1; // valor en el espacio de cámara
        double rayDirX = player.dirX + player.planeX * cameraX;
        double rayDirY = player.dirY + player.planeY * cameraX;

        int mapX = (int)player.posX;
        int mapY = (int)player.posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = fabs(1 / rayDirX);
        double deltaDistY = fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;
        int hit = 0;
        int side;

        if(rayDirX < 0) {
            stepX = -1;
            sideDistX = (player.posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player.posX) * deltaDistX;
        }

        if(rayDirY < 0) {
            stepY = -1;
            sideDistY = (player.posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player.posY) * deltaDistY;
        }

        while(hit == 0) {
            if(sideDistX < sideDistY) {
                sideDistX += deltaDistX;
                mapX += stepX;
                side = 0;
            } else {
                sideDistY += deltaDistY;
                mapY += stepY;
                side = 1;
            }
            if(worldMap[mapY][mapX] > 0) hit = 1;
        }

        if(side == 0) perpWallDist = (mapX - player.posX + (1 - stepX) / 2) / rayDirX;
        else          perpWallDist = (mapY - player.posY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(screenHeight / perpWallDist);

        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if(drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if(drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        int color;
        switch(worldMap[mapY][mapX]) {
            case 1: color = 0xFF0000; break; // rojo
            case 2: color = 0x00FF00; break; // verde
            case 3: color = 0x0000FF; break; // azul
            case 4: color = 0xFFFFFF; break; // blanco
            default: color = 0xFFFF00; break; // amarillo
        }

        if(side == 1) color = color / 2;

        for(int y = drawStart; y <= drawEnd; y++) {
            draw_pixel(x, y, color);
        }
    }
}

int main() {
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, screenWidth, screenHeight, "Raycaster");
    mlx.img = mlx_new_image(mlx.mlx, screenWidth, screenHeight);
    mlx.data_addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.size_line, &mlx.endian);

    while(1) {
        render();
        mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
        mlx_do_sync(mlx.mlx); // Sincronizar para reducir el parpadeo
    }

    mlx_destroy_image(mlx.mlx, mlx.img);
    mlx_destroy_window(mlx.mlx, mlx.win);
    return 0;
}
