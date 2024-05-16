#include "../include/cubed.h"

int expose(t_data *w1)
{
    char **worldMap = w1->table;
    
    double posX = 1, posY = 1;  //x and y start position
    double dirX = -1, dirY = 0; //initial direction vector
    double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

    /*double time = 0; //time of current frame
    double oldTime = 0; //time of previous frame
*/
    int     x;
    while(1)
    {
        x = 0;
        while (x < w1->lenght)
        {
            double cameraX = 2 * x / (double)w1->lenght - 1; //x-coordinate in camera space
            double rayDirX = dirX + planeX * cameraX;
            double rayDirY = dirY + planeY * cameraX;
            int mapX = posX;
            int mapY = posY;

            double sideDistX;
            double sideDistY;

            double deltaDistX = (rayDirX == 0) ? 1e30 : fabs(1 / rayDirX);
            double deltaDistY = (rayDirY == 0) ? 1e30 : fabs(1 / rayDirY);

            double perpWallDist;

            //what direction to step in x or y-direction (either +1 or -1)
            int stepX;
            int stepY;

            int hit = 0; //was there a wall hit?
            int side; //was a NS or a EW wall hit?

            if(rayDirX < 0)
            {
                stepX = -1;
                sideDistX = (posX - mapX) * deltaDistX;
            }
            else
            {
                stepX = 1;
                sideDistX = (mapX + 1.0 - posX) * deltaDistX;
            }
            if(rayDirY < 0)
            {
                stepY = -1;
                sideDistY = (posY - mapY) * deltaDistY;
            }
            else
            {
                stepY = 1;
                sideDistY = (mapY + 1.0 - posY) * deltaDistY;
            }
            while(hit == 0)
            {
                //jump to next map square, either in x-direction, or in y-direction
                if(sideDistX < sideDistY)
                {
                    sideDistX += deltaDistX;
                    mapX += stepX;
                    side = 0;
                }
                else
                {
                    sideDistY += deltaDistY;
                    mapY += stepY;
                    side = 1;
                }
                //Check if ray has hit a wall
                if(worldMap[mapX][mapY] > 0)
                    hit = 1;
            }
            if(side == 0)
                perpWallDist = (sideDistX - deltaDistX);
            else
                perpWallDist = (sideDistY - deltaDistY);

            int lineHeight = (int)(w1->width / perpWallDist);
            
            int drawStart = -lineHeight / 2 + w1->width / 2;
            if(drawStart < 0)
                drawStart = 0;
            
            int drawEnd = lineHeight / 2 + w1->width / 2;
            if(drawEnd >= w1->width)
                drawEnd = w1->width - 1;

            //int ystart = drawStart;
            /*while (ystart > drawEnd)
            {
                //mlx_pixel_put(w1->mlx, w1->win, x, ystart, 255);
            //    mlx_put_image_to_window(w1->mlx, w1->win, w1->img.grass, x * 45, ystart * 45);
                //mlx_pixel_put(w1->mlx, w1->win, x, 40, 255);
                ystart -= 1;
            }*/
            //mlx_put_image_to_window(w1->mlx, w1->win, w1->img.grass, x, ystart);

            x++;
        }
    }
    return (0);
}