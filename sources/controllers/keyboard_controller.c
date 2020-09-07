#include "../../includes/wolf3d.h"

void shift_w(t_db *data)
{
	if (!data->map.cell[(data->player.y - 1) * data->map.len + data->player.x].wall)
		data->player.y--;
}

void shift_a(t_db *data)
{
	if (!data->map.cell[data->player.y * data->map.len + data->player.x - 1].wall)
			data->player.x--;
}

void shift_s(t_db *data)
{
	if (!data->map.cell[(data->player.y + 1) * data->map.len + data->player.x].wall)
		data->player.y++;
}

void shift_d(t_db *data)
{
	if (!data->map.cell[data->player.y * data->map.len + data->player.x + 1].wall)
		data->player.x++;
}

void shift_right(t_db *data)
{
	if (data->player.pov == 355.f)
		data->player.pov = 0;
	else
		data->player.pov += 5.f;
}

void shift_left(t_db *data)
{
	if (data->player.pov == 0)
		data->player.pov = 355.f;
	else
		data->player.pov -= 5.f;
}

void 		keyboard_controller(SDL_Event *event, t_db *data)
{
	if (event->type == SDL_KEYDOWN)
	{
		event->key.keysym.sym == SDLK_w ? shift_w(data) : 0;
		event->key.keysym.sym == SDLK_a ? shift_a(data) : 0;
		event->key.keysym.sym == SDLK_s ? shift_s(data) : 0;
		event->key.keysym.sym == SDLK_d ? shift_d(data) : 0;

		event->key.keysym.sym == SDLK_RIGHT ? shift_right(data) : 0;
		event->key.keysym.sym == SDLK_LEFT ? shift_left(data) : 0;
	}
//	ft_printf("key_number = %d\n", event->key.keysym.sym);
}
