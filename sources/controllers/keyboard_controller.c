#include "../../includes/wolf3d.h"

void shift_up(t_db *data)
{
	if (!data->map.cell[(int)(data->player.posY- 1) * data->map.len + (int)(data->player.posX + data->player.dirX * 0.1f)].wall)
		data->player.posX += data->player.dirX * 0.1f;
	if (!data->map.cell[(int)(data->player.posY + data->player.dirY * 0.1f - 1) * data->map.len + (int)data->player.posX].wall)
		data->player.posY += data->player.dirY * 0.1f;
}

void shift_left(t_db *data)
{
	float oldDirX;
	float oldPlaneX;
	float rotSpeed = 0.0174533f;

	oldDirX = data->player.dirX;
	oldPlaneX = data->player.planeX;
	data->player.dirX = data->player.dirX * cos(rotSpeed) - data->player.dirY * sin(rotSpeed);
	data->player.dirY = oldDirX * sin(rotSpeed) + data->player.dirY * cos(rotSpeed);
	data->player.planeX = data->player.planeX * cos(rotSpeed) - data->player.planeY * sin(rotSpeed);
	data->player.planeY = oldPlaneX * sin(rotSpeed) + data->player.planeY * cos(rotSpeed);
}

void shift_down(t_db *data)
{
	if (!data->map.cell[(int)(data->player.posY- 1) * data->map.len + (int)(data->player.posX - data->player.dirX * 0.1f)].wall)
		data->player.posX -= data->player.dirX * 0.1f;
	if (!data->map.cell[(int)(data->player.posY - data->player.dirY * 0.1f - 1) * data->map.len + (int)data->player.posX].wall)
		data->player.posY -= data->player.dirY * 0.1f;
}

void shift_right(t_db *data)
{
	float oldDirX;
	float oldPlaneX;
	float rotSpeed = 0.0174533f;

	oldDirX = data->player.dirX;
	oldPlaneX = data->player.planeX;
	data->player.dirX = data->player.dirX * cos(-rotSpeed) - data->player.dirY * sin(-rotSpeed);
	data->player.dirY = oldDirX * sin(-rotSpeed) + data->player.dirY * cos(-rotSpeed);
	data->player.planeX = data->player.planeX * cos(-rotSpeed) - data->player.planeY * sin(-rotSpeed);
	data->player.planeY = oldPlaneX * sin(-rotSpeed) + data->player.planeY * cos(-rotSpeed);
}

void shift(t_db *data, SDL_Event *event)
{
	event->key.keysym.sym == SDLK_w ? shift_right(data) : 0;
	event->key.keysym.sym == SDLK_a ? shift_up(data) : 0;
	event->key.keysym.sym == SDLK_s ? shift_left(data) : 0;
	event->key.keysym.sym == SDLK_d ? shift_down(data) : 0;
}

void 		keyboard_controller(SDL_Event *event, t_db *data)
{
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_w || event->key.keysym.sym == SDLK_a
			|| event->key.keysym.sym == SDLK_s || event->key.keysym.sym == SDLK_d)
			shift(data, event);
	}
//	ft_printf("key_number = %d\n", event->key.keysym.sym);
}
