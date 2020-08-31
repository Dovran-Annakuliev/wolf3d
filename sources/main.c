#include "../includes/wolf3d.h"

int main(int ac, char **av)
{
	t_db *data;
	SDL_Event event;
	int quit;
	int *res;

	if (ac != 2)
		error(1);
	data_init(av[1], data);
	while (quit != 1)
	{
		SDL_RenderClear(data->sld.renderer);
//		res = render(data->cl, data->width, data->height);
		update_texture(data->sld.texture, data->sld.width, data->sld.height);//, res);
		SDL_RenderCopy(data->sld.renderer, data->sld.texture, NULL, NULL);
		SDL_RenderPresent(data->sld.renderer);
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
				quit = 1;
//			else
//				controller(&e);
		}
	}
	close_wolf(data);
	return (0);
}
