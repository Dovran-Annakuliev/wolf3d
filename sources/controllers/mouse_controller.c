#include "../../includes/wolf3d.h"

void x_motion_p(t_db *data, int x_w, int y_w)
{
	if (data->player.pov == 357.f)
		data->player.pov = 0;
	else
		data->player.pov += 3.f;
	data->player.x_ms = x_w;
	if (x_w >= data->sdl.width * 0.99)
		SDL_WarpMouseInWindow(data->sdl.window, 100, y_w);
}

void x_motion_m(t_db *data, int x_w, int y_w)
{
	if (data->player.pov == 0)
		data->player.pov = 357.f;
	else
		data->player.pov -= 3.f;
	data->player.x_ms = x_w;
	if (x_w == 0)
		SDL_WarpMouseInWindow(data->sdl.window, data->sdl.width * 0.99 - 10, y_w);
}

void		mouse_controller(SDL_Event *event, t_db *data)
{
	int x;
	int y;

	SDL_GetMouseState(&x, &y);
	if (event->type == SDL_MOUSEMOTION)
	{
		x >= data->player.x_ms
		? x_motion_p(data, x, y)
		: x_motion_m(data, x, y);
	}
//	ft_printf("x = %d, y = %d\n", x, y);
}
