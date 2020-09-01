#include "../includes/wolf3d.h"

void error(int er, const char *message)
{
	if (er == MALLOC_ERROR)
		ft_printf("Malloc error\n");
	else if (er == SDL_INIT_ERROR)
		ft_printf("SDL_init error: %s\n", message);
	else if (er == IMG_INIT_ERROR)
		ft_printf("IMG_init error: %s\n", message);
	else if (er == WINDOW_CREATE_ERROR)
		ft_printf("Window_create error: %s\n", message);
	else if (er == RENDER_INIT_ERROR)
		ft_printf("Render_init error: %s\n", message);
	else if (er == TEXTURE_LOAD_ERROR)
		ft_printf("SDL_texture error: %s\n", message);
	else if (er == TEXTURE_LOCK_ERROR)
		ft_printf("SDL_texture_lock error: %s\n", message);
	else if (er == INVALID_ARGUMENTS)
		ft_printf("Invalid number arguments\n");
	else if (er == INVALID_MAP)
		ft_printf("Invalid map\n");
	exit(0);
}

void 	close_wolf(t_db *data)
{
	SDL_DestroyTexture(data->sdl.texture);
	IMG_Quit();
	SDL_DestroyRenderer(data->sdl.renderer);
	SDL_DestroyWindow(data->sdl.window);
	SDL_Quit();
	free(data);
	data = NULL;
}
