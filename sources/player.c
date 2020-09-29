#include "../includes/wolf3d.h"

//void draw_fov(t_db *data, float angle, int i)
//{
//	float view_line;
//	float x;
//	float y;
//	int k;
//	float line;
//
//	view_line = 0;
//	int shift = data->map.fill / 2;
////	while (1)
////	{
////		x = data->player.x * data->map.fill + view_line * cosf(angle);
////		y = data->player.y * data->map.fill + view_line * sinf(angle);
////		k = (int)(x / data->map.fill) + (int)(y / data->map.fill) * data->map.len;
////		if (data->map.cell[k].wall != 0)
////			break;
////		view_line += 0.05f;
////	}
//	while (view_line <= 20)
//	{
//		x = data->player.x + view_line * cosf(angle);
//		y = data->player.y + view_line * sinf(angle);
//		k = (int)x + (int)y * data->map.len;
//		if (data->map.cell[k].wall != 0)
//			break;
//		view_line += 0.0001f;
//	}
//
//	float hitx = x - floorf(x + 0.5f);
//	float hity = y - floorf(y + 0.5f);
//	int side;
//	if (SDL_fabs(hity) < 0.0001 && hity < 0)
//		side = 0;
//	else if (SDL_fabs(hity) < 0.0001 && hity > 0)
//		side = 1;
//	else
//		side = (SDL_fabs(hitx) < 0.0001 && hitx < 0) ? 2 : 3;
//
//	SDL_SetRenderDrawColor(data->sdl.renderer, 0, 0, 255, 255);
//	SDL_RenderDrawLineF(data->sdl.renderer, data->player.x * data->map.fill,
//					 data->player.y * data->map.fill, x * data->map.fill, y * data->map.fill);
//	if (side == 0)
//		SDL_SetRenderDrawColor(data->sdl.renderer, 0, 255, 0, 255);
//	else if (side == 1)
//		SDL_SetRenderDrawColor(data->sdl.renderer, 255, 0, 0, 255);
//	else if (side == 2)
//		SDL_SetRenderDrawColor(data->sdl.renderer, 0, 0, 255, 255);
//	else if (side == 3)
//		SDL_SetRenderDrawColor(data->sdl.renderer, 0, 0, 0, 255);
//
//
//	float line2 = data->sdl.height / (view_line * cosf(angle - data->player.pov * (float)M_PI / 180)) / 2;
//	SDL_RenderDrawLineF(data->sdl.renderer, i, data->sdl.height / 2 - line2, i, data->sdl.height / 2 + line2);
//}

//void player_present(t_db *data)
//{
//	float angle;
//	float step;
//	float fin;
//
//
//
//	angle = (data->player.pov - data->player.fov / 2) * (float)M_PI / 180;
//	step = (data->player.fov * (float)M_PI / 180) / data->sdl.width;
//	fin = (data->player.pov + data->player.fov / 2) * (float)M_PI / 180;
//
//	int i = 0;
//	while (angle <= fin)
//	{
//		draw_fov(data, angle, i++);
//		angle += step;
//	}
//	ft_printf("pov angle = %f\n", data->player.pov);

//	ft_printf("line_x = %d, line_y = %d\n", data->player.x * data->map.fill, data->player.y * data->map.fill);
//	ft_printf("x = %d, y = %d\n", x, y);

//	print_rect(rect);
//}


void player_present(t_db *data)
{
	int w = data->sdl.width;
	int h = data->sdl.height;

	double posX = 1.5 * data->map.fill, posY = 1.5 * data->map.fill;
	double dirX = 1, dirY = 0;
	double planeX = 0, planeY = 0.66;
//
//	double posX = 22, posY = 12;  //x and y start position
//	double dirX = -1, dirY = 0; //initial direction vector
//	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane

	for(int x = 0; x < w; x++)
	{
		double cameraX = 2 * x / (double) w - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)posX / data->map.fill;
		int mapY = (int)posY / data->map.fill;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		double deltaDistX = (rayDirY == 0) ? 0 : ((rayDirX == 0) ? 1 : fabs(1 / rayDirX));
		double deltaDistY = (rayDirX == 0) ? 0 : ((rayDirY == 0) ? 1 : fabs(1 / rayDirY));
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (posX - mapX) * deltaDistX;
		} else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - posX) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (posY - mapY) * deltaDistY;
		} else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - posY) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			} else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (data->map.cell[mapY * data->map.len + mapX].wall == 1)
				hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0)
			perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		else
			perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int) (h / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + h / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + h / 2;
		if (drawEnd >= h)
			drawEnd = h - 1;

		if (side == 0)
			SDL_SetRenderDrawColor(data->sdl.renderer, 0, 255, 0, 255);
		else
			SDL_SetRenderDrawColor(data->sdl.renderer, 255, 0, 0, 255);

		SDL_RenderDrawLineF(data->sdl.renderer, x, drawStart, x, drawEnd);
	}
}
