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
	while (1)
	{
		x = data->player.x * data->map.fill + view_line * cos(angle) + shift;
		y = data->player.y * data->map.fill + view_line * sin(angle) + shift;
		k = (int)(x / data->map.fill) + (int)(y / data->map.fill) * data->map.len;
		if (data->map.cell[k].wall != 0)
			break;
		view_line += 0.05f;
	}
	line = ft_abs(y - data->player.y * data->map.fill + shift) / sin(angle);
	SDL_RenderDrawLineF(data->sdl.renderer, data->player.x * data->map.fill + shift, data->player.y * data->map.fill + shift, x, y);
//	SDL_RenderDrawLineF(data->sdl.renderer, data->sdl.height - line, i, data->sdl.height - line, i);
}

void player_present(t_db *data)
{
	float angle;
	float step;
	float fin;

	SDL_Rect rect = create_rect(data->map.fill, data->map.fill, data->player.x * data->map.fill, data->player.y * data->map.fill);
	draw_rect(rect, (cl_float4){255, 0, 0, 255}, data->sdl.renderer);

	angle = data->player.pov - data->player.fov / 2;
	step = data->player.fov / 512;
	fin = data->player.pov + data->player.fov / 2;

	int i = 0;
	while (angle <= fin)
	{
		draw_fov(data, angle, i++);

//		printf("angle = %f\n", angle);
		angle += step;
	}
//	draw_fov(data, data->player.pov);
//	draw_fov(data, data->player.pov - data->player.fov / 2);
//	draw_fov(data, data->player.pov + data->player.fov / 2);

//	ft_printf("pov angle = %f\n", data->player.pov);

//	ft_printf("line_x = %d, line_y = %d\n", data->player.x * data->map.fill, data->player.y * data->map.fill);
//	ft_printf("x = %d, y = %d\n", x, y);

//	print_rect(rect);
}
