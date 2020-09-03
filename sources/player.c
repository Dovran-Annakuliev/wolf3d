#include "../includes/wolf3d.h"

void print_rect(SDL_Rect rect)
{
	ft_printf("h = %d, w = %d, x = %d, y = %d\n", rect.h, rect.w, rect.x, rect.y);
}

void player_present(t_db *data)
{
	SDL_Rect rect = create_rect(data->map.rect, data->map.rect, data->player.x * data->map.rect, data->player.y * data->map.rect);
	draw_rect(rect, (cl_float4){255, 0, 0, 255}, data->sdl.renderer);

	print_rect(rect);
}
