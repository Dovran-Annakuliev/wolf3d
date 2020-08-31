#include "../includes/wolf3d.h"

void error(int er)
{
	if (er == 1)
		ft_printf("invalid number arguments\n");
	else if (er == 2)
		ft_printf("invalid map\n");
	else if (er == 3)
		ft_printf("SDL error\n");
	exit(0);
}

void 	close_wolf(t_db *data)
{
	SDL_DestroyTexture(data->sld.texture);
	IMG_Quit();
	SDL_DestroyRenderer(data->sld.renderer);
	SDL_DestroyWindow(data->sld.window);
	SDL_Quit();
	free(data);
	data = NULL;
}
