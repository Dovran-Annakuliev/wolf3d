#include "../includes/wolf3d.h"

int main(int ac, char **av)
{
	t_db *data;
	SDL_Event event;
	int quit;
	int *res;

	if (ac != 2)
		error(INVALID_ARGUMENTS, NULL);
	data = data_init(av[1]);//, data);
	quit = 0;
	while (quit != 1)
	{
		SDL_RenderClear(data->sdl.renderer);
//		res = render(data->cl, data->width, data->height);
//		update_texture(data);//, res);
		SDL_RenderCopy(data->sdl.renderer, data->sdl.texture, NULL, NULL);
		SDL_RenderPresent(data->sdl.renderer);
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
