#include "../includes/wolf3d.h"

void draw_fov(t_db *data, float angle, int i)
{
	float view_line;
	float x;
	float y;
	int k;
	float line;

	view_line = 0;
	int shift = data->map.fill / 2;
//	while (1)
//	{
//		x = data->player.x * data->map.fill + view_line * cosf(angle);
//		y = data->player.y * data->map.fill + view_line * sinf(angle);
//		k = (int)(x / data->map.fill) + (int)(y / data->map.fill) * data->map.len;
//		if (data->map.cell[k].wall != 0)
//			break;
//		view_line += 0.05f;
//	}
	while (1)
	{
		x = data->player.x + view_line * cosf(angle);
		y = data->player.y + view_line * sinf(angle);
		k = (int)x + (int)y * data->map.len;
		if (data->map.cell[k].wall != 0)
			break;
		view_line += 0.05f;
	}
	SDL_SetRenderDrawColor(data->sdl.renderer, 0, 0, 255, 255);
	SDL_RenderDrawLineF(data->sdl.renderer, data->player.x * data->map.fill + shift,
					 data->player.y * data->map.fill + shift, x * data->map.fill, y * data->map.fill);

//	line = sqrtf(powf((data->player.x * data->map.fill - x),(data->player.x * data->map.fill - x))
//			  + powf((data->player.y * data->map.fill - y), (data->player.y * data->map.fill - y)));

//	line = fabsf(y - data->player.y * data->map.fill + shift) / sinf(angle);
	SDL_SetRenderDrawColor(data->sdl.renderer, 255, 0, 0, 255);
	float line2 = data->sdl.height / (view_line * cosf(angle - data->player.pov));
	SDL_RenderDrawLineF(data->sdl.renderer, i, data->sdl.height / 2 - line2, i, data->sdl.height / 2 + line2);
}

void player_present(t_db *data)
{
	float angle;
	float step;
	float fin;



	angle = (data->player.pov - data->player.fov / 2) * (float)M_PI / 180;
	step = (data->player.fov * (float)M_PI / 180) / data->sdl.width;
	fin = (data->player.pov + data->player.fov / 2) * (float)M_PI / 180;

	int i = 0;
	while (angle <= fin)
	{
		draw_fov(data, angle, i++);
		angle += step;
	}
//	ft_printf("pov angle = %f\n", data->player.pov);

//	ft_printf("line_x = %d, line_y = %d\n", data->player.x * data->map.fill, data->player.y * data->map.fill);
//	ft_printf("x = %d, y = %d\n", x, y);

//	print_rect(rect);
}
