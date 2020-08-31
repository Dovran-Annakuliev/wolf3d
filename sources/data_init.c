#include "../includes/wolf3d.h"

void init_sdl(t_db *data)
{
	SDL_Init(SDL_INIT_EVERYTHING) < 0 ? error(3) : 0;
	data->sld.window = SDL_CreateWindow("wolf3d", 0, 0, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	SDL_GetWindowSize(data->sld.window, data->sld.width, data->sld.height);
	IMG_Init(IMG_INIT_PNG) < 0 ? error(3) : 0;
	data->sld.renderer = SDL_CreateRenderer(data->sld.window, -1, SDL_RENDERER_ACCELERATED);
	!(data->sld.renderer) ? error(3) : 0;
	data->sld.texture = SDL_CreateTexture(data->sld.renderer,
									   SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING,
									   data->sld.width, data->sld.height);
	!(data->sld.texture) ? error(3) : 0;
}

void	data_init(char *source, t_db *data)
{
	if (!(data = (t_db*)malloc(sizeof(t_db))))
		error(0);
	read_arg(source, data);
	init_sdl(data);

/*------------------------------DELETE ME----------------------------------*/
	int i = -1;
	while (++i < data->map.heg)
	{
		int j = -1;
		while (++j < data->map.len)
			if (data->map.map[i * data->map.len + j].status != '0')
				printf("%c ", data->map.map[i * data->map.len + j].status);
			else
				printf("%d ", data->map.map[i * data->map.len + j].wall);

		printf("\n");
	}
/*------------------------------DELETE ME----------------------------------*/

}
