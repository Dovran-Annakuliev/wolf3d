#include "../includes/wolf3d.h"

void init_sdl(t_db *data)
{
	SDL_Init(SDL_INIT_EVERYTHING) < 0 ? error(SDL_INIT_ERROR, SDL_GetError()) : 0;
	IMG_Init(IMG_INIT_PNG) < 0 ? error(IMG_INIT_ERROR, SDL_GetError()) : 0;
	data->sdl.window = SDL_CreateWindow("wolf3d", 0, 0, 0, 0, SDL_WINDOW_FULLSCREEN_DESKTOP);
	!(data->sdl.window) ? error(WINDOW_CREATE_ERROR, SDL_GetError()) : 0;
	SDL_GetWindowSize(data->sdl.window, &data->sdl.width, &data->sdl.height);
	ft_printf("width = %d, height = %d\n", data->sdl.width, data->sdl.height);
	data->sdl.renderer = SDL_CreateRenderer(data->sdl.window, -1, SDL_RENDERER_ACCELERATED);
	!(data->sdl.renderer) ? error(RENDER_INIT_ERROR, SDL_GetError()) : 0;
	data->sdl.texture = SDL_CreateTexture(data->sdl.renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, data->sdl.width, data->sdl.height);
	!(data->sdl.texture) ? error(TEXTURE_LOAD_ERROR, SDL_GetError()) : 0;
}

t_db 	*data_init(char *source)//, t_db *data)
{
	t_db *data;
	if (!(data = (t_db*)malloc(sizeof(t_db))))
		error(MALLOC_ERROR, NULL);
	read_arg(source, data);
	init_sdl(data);

/*------------------------------DELETE ME----------------------------------*/
	int i = -1;
	ft_printf("\nmap: \n");
	while (++i < data->map.heg)
	{
		int j = -1;
		while (++j < data->map.len)
			if (data->map.map[i * data->map.len + j].status != '0')
				ft_printf("%c ", data->map.map[i * data->map.len + j].status);
			else
				ft_printf("%d ", data->map.map[i * data->map.len + j].wall);

		ft_printf("\n");
	}
	ft_printf("\n");
/*------------------------------DELETE ME----------------------------------*/

	return (data);
}