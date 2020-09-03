#include "../../includes/wolf3d.h"

void 		keyboard_controller(SDL_Event *event, t_db *data)
{
	if (event->type == SDL_KEYDOWN)
	{
		event->key.keysym.sym == SDLK_w ?  data->player.y-- : 0;
		event->key.keysym.sym == SDLK_a ?  data->player.x-- : 0;
		event->key.keysym.sym == SDLK_s ?  data->player.y++ : 0;
		event->key.keysym.sym == SDLK_d ?  data->player.x++ : 0;
	}
	ft_printf("key_number = %d\n", event->key.keysym.sym);
}
