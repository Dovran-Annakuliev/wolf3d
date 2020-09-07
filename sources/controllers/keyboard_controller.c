#include "../../includes/wolf3d.h"

void shift_up(t_db *data)
{
	if (!data->map.cell[(data->player.y - 1) * data->map.len + data->player.x].wall)
		data->player.y--;
}

void shift_left(t_db *data)
{
	if (!data->map.cell[data->player.y * data->map.len + data->player.x - 1].wall)
			data->player.x--;
}

void shift_down(t_db *data)
{
	if (!data->map.cell[(data->player.y + 1) * data->map.len + data->player.x].wall)
		data->player.y++;
}

void shift_right(t_db *data)
{
	if (!data->map.cell[data->player.y * data->map.len + data->player.x + 1].wall)
		data->player.x++;
}

void rot_right(t_db *data)
{
	if (data->player.pov >= 357.f)
		data->player.pov = 0;
	else
		data->player.pov += 3.f;
	ft_printf("pov = %f\n", data->player.pov);
}

void rot_left(t_db *data)
{
	if (data->player.pov <= 0)
		data->player.pov = 357.f;
	else
		data->player.pov -= 3.f;
	ft_printf("pov = %f\n", data->player.pov);
}

void shift(t_db *data, SDL_Event *event)
{
	if (data->player.pov >= 315.f || data->player.pov < 45.f)
	{
		event->key.keysym.sym == SDLK_w ? shift_right(data) : 0;
		event->key.keysym.sym == SDLK_a ? shift_up(data) : 0;
		event->key.keysym.sym == SDLK_s ? shift_left(data) : 0;
		event->key.keysym.sym == SDLK_d ? shift_down(data) : 0;
	}
	else if (data->player.pov >= 45.f && data->player.pov < 135.f)
	{
		event->key.keysym.sym == SDLK_w ? shift_down(data) : 0;
		event->key.keysym.sym == SDLK_a ? shift_right(data) : 0;
		event->key.keysym.sym == SDLK_s ? shift_up(data) : 0;
		event->key.keysym.sym == SDLK_d ? shift_left(data) : 0;
	}
	else if (data->player.pov >= 135.f && data->player.pov < 225.f)
	{
		event->key.keysym.sym == SDLK_w ? shift_left(data) : 0;
		event->key.keysym.sym == SDLK_a ? shift_down(data) : 0;
		event->key.keysym.sym == SDLK_s ? shift_right(data) : 0;
		event->key.keysym.sym == SDLK_d ? shift_up(data) : 0;
	}
	else if (data->player.pov >= 225.f && data->player.pov < 315.f)
	{
		event->key.keysym.sym == SDLK_w ? shift_up(data) : 0;
		event->key.keysym.sym == SDLK_a ? shift_left(data) : 0;
		event->key.keysym.sym == SDLK_s ? shift_down(data) : 0;
		event->key.keysym.sym == SDLK_d ? shift_right(data) : 0;
	}
}

void 		keyboard_controller(SDL_Event *event, t_db *data)
{
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_w || event->key.keysym.sym == SDLK_a
			|| event->key.keysym.sym == SDLK_s || event->key.keysym.sym == SDLK_d)
			shift(data, event);

		event->key.keysym.sym == SDLK_RIGHT ? rot_right(data) : 0;
		event->key.keysym.sym == SDLK_LEFT ? rot_left(data) : 0;
	}
//	ft_printf("key_number = %d\n", event->key.keysym.sym);
}
