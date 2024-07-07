#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mlx/mlx.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

#define moveSpeed 0.05
#define rotSpeed 0.03

#define INITIAL_DIRECTION 'N' // Cambia esta macro a 'N', 'S', 'E', 'W' según la dirección deseada

typedef struct s_player {
    double posX, posY;
    double dirX, dirY;
    double planeX, planeY;
} t_player;

typedef struct s_mlx {
    void *mlx;
    void *win;
    void *img;
    char *data_addr;
    int bpp;
    int size_line;
    int endian;
} t_mlx;

int worldMap[mapHeight][mapWidth] = {
    {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
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

t_player player = {4.5, 6.5, 0.0, 0.0, 0.0, 0.0};
t_mlx mlx;

void draw_pixel(int x, int y, int color) {
    if (x >= 0 && x < screenWidth && y >= 0 && y < screenHeight) {
        char *pixel = mlx.data_addr + (y * mlx.size_line + x * (mlx.bpp / 8));
        *(unsigned int*)pixel = color;
    }
}

void set_initial_direction() {
    #if INITIAL_DIRECTION == 'N'
        player.dirX = 0;
        player.dirY = -1;
        player.planeX = 0.66;
        player.planeY = 0;
    #elif INITIAL_DIRECTION == 'S'
        player.dirX = 0;
        player.dirY = 1;
        player.planeX = -0.66;
        player.planeY = 0;
    #elif INITIAL_DIRECTION == 'E'
        player.dirX = 1;
        player.dirY = 0;
        player.planeX = 0;
        player.planeY = 0.66;
    #elif INITIAL_DIRECTION == 'W'
        player.dirX = -1;
        player.dirY = 0;
        player.planeX = 0;
        player.planeY = -0.66;
    #endif
}

void render() {
    // Dibujar cielo y suelo
    for (int x = 0; x < screenWidth; x++) {
        for (int y = 0; y < screenHeight / 2; y++) {
            draw_pixel(x, y, 0x87CEEB); // Color del cielo
        }
        for (int y = screenHeight / 2; y < screenHeight; y++) {
            draw_pixel(x, y, 0x8B4513); // Color del suelo
        }
    }

    for (int x = 0; x < screenWidth; x++) {
        double cameraX = 2 * x / (double)screenWidth - 1;
        double rayDirX = player.dirX + player.planeX * cameraX;
        double rayDirY = player.dirY + player.planeY * cameraX;

        int mapX = (int)player.posX;
        int mapY = (int)player.posY;

        double sideDistX;
        double sideDistY;

        double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
        double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);
        double perpWallDist;

        int stepX;
        int stepY;
        int hit = 0;
        int side;

        if (rayDirX < 0) {
            stepX = -1;
            sideDistX = (player.posX - mapX) * deltaDistX;
        } else {
            stepX = 1;
            sideDistX = (mapX + 1.0 - player.posX) * deltaDistX;
        }
        
        if (rayDirY < 0) {
            stepY = -1;
            sideDistY = (player.posY - mapY) * deltaDistY;
        } else {
            stepY = 1;
            sideDistY = (mapY + 1.0 - player.posY) * deltaDistY;
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

            if (worldMap[mapX][mapY] > 0) hit = 1;
        }

        if (side == 0) perpWallDist = (mapX - player.posX + (1 - stepX) / 2) / rayDirX;
        else perpWallDist = (mapY - player.posY + (1 - stepY) / 2) / rayDirY;

        int lineHeight = (int)(screenHeight / perpWallDist);

        int drawStart = -lineHeight / 2 + screenHeight / 2;
        if (drawStart < 0) drawStart = 0;
        int drawEnd = lineHeight / 2 + screenHeight / 2;
        if (drawEnd >= screenHeight) drawEnd = screenHeight - 1;

        int color;
        switch (worldMap[mapX][mapY]) {
            case 1: color = 0xFF0000; break; // rojo
            case 2: color = 0x00FF00; break; // verde
            case 3: color = 0x0000FF; break; // azul
            case 4: color = 0xFFFFFF; break; // blanco
            default: color = 0xFFFF00; break; // amarillo
        }

        if (side == 1) color = color / 2;

        for (int y = drawStart; y <= drawEnd; y++) {
            draw_pixel(x, y, color);
        }
    }
}

int key_press(int keycode, void *param) {
    (void)param;
    if (keycode == 65307) { // ESC key
        mlx_destroy_window(mlx.mlx, mlx.win);
        exit(0);
    }
    if (keycode == 119) { // W key
        if (worldMap[(int)(player.posX + player.dirX * moveSpeed)][(int)player.posY] == 0) player.posX += player.dirX * moveSpeed;
        if (worldMap[(int)player.posX][(int)(player.posY + player.dirY * moveSpeed)] == 0) player.posY += player.dirY * moveSpeed;
    }
    if (keycode == 115) { // S key
        if (worldMap[(int)(player.posX - player.dirX * moveSpeed)][(int)player.posY] == 0) player.posX -= player.dirX * moveSpeed;
        if (worldMap[(int)player.posX][(int)(player.posY - player.dirY * moveSpeed)] == 0) player.posY -= player.dirY * moveSpeed;
    }
    if (keycode == 100) { // A key
        double oldDirX = player.dirX;
        player.dirX = player.dirX * cos(rotSpeed) - player.dirY * sin(rotSpeed);
        player.dirY = oldDirX * sin(rotSpeed) + player.dirY * cos(rotSpeed);
        double oldPlaneX = player.planeX;
        player.planeX = player.planeX * cos(rotSpeed) - player.planeY * sin(rotSpeed);
        player.planeY = oldPlaneX * sin(rotSpeed) + player.planeY * cos(rotSpeed);
    }
    if (keycode == 97) { // D key
        double oldDirX = player.dirX;
        player.dirX = player.dirX * cos(-rotSpeed) - player.dirY * sin(-rotSpeed);
        player.dirY = oldDirX * sin(-rotSpeed) + player.dirY * cos(-rotSpeed);
        double oldPlaneX = player.planeX;
        player.planeX = player.planeX * cos(-rotSpeed) - player.planeY * sin(-rotSpeed);
        player.planeY = oldPlaneX * sin(-rotSpeed) + player.planeY * cos(-rotSpeed);
    }
    return 0;
}

int main_loop(void *param) {
    (void)param;
    render();
    mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
    return 0;
}

int main() {
    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, screenWidth, screenHeight, "Raycaster");
    mlx.img = mlx_new_image(mlx.mlx, screenWidth, screenHeight);
    mlx.data_addr = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.size_line, &mlx.endian);

    set_initial_direction(); // Configurar la dirección inicial del jugador

    mlx_hook(mlx.win, 2, 1L<<0, key_press, (void*)0);
    mlx_loop_hook(mlx.mlx, main_loop, (void*)0);

    mlx_loop(mlx.mlx);

    mlx_destroy_image(mlx.mlx, mlx.img);
    mlx_destroy_window(mlx.mlx, mlx.win);
    return 0;
}
