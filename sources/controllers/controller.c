#include "../../includes/wolf3d.h"

void		controller(SDL_Event *event, t_db *data)
{
	if (event->type == SDL_KEYDOWN)
		keyboard_controller(event, data);
	if (event->type == SDL_MOUSEMOTION || event->type == SDL_MOUSEBUTTONDOWN || event->type == SDL_MOUSEBUTTONUP)
		mouse_controller(event, data);
}
