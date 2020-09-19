#include "../includes/wolf3d.h"

//rewrite to draw rectangle by yourself

SDL_Rect	create_rect(int h, int w, int x, int y)
{
	SDL_Rect rect;
	rect.h = h;
	rect.w = w;
	rect.x = x;
	rect.y = y;
	return (rect);

}

void 	draw_rect(SDL_Rect rect, cl_float4 color, SDL_Renderer *renderer)
{
	SDL_SetRenderDrawColor(renderer, color.x, color.y, color.z, color.w);
	SDL_RenderFillRect(renderer, &rect);
}

void create_background(t_db *data)
{
	Uint32				*pixels;
	SDL_PixelFormat		*format;
	int					pitch;
	int i;

	if (SDL_LockTexture(data->sdl.texture, NULL, (void **) &pixels, &pitch) != 0)
		error(TEXTURE_LOCK_ERROR, SDL_GetError());
	format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	i = -1;
	while (++i < data->sdl.width * data->sdl.height / 2)
		pixels[i] = SDL_MapRGBA(format, 255, 255, 255, 255);
	while (++i < data->sdl.width * data->sdl.height)
		pixels[i] = SDL_MapRGBA(format, 204, 204, 204, 255);
	SDL_UnlockTexture(data->sdl.texture);
	SDL_RenderCopy(data->sdl.renderer, data->sdl.texture, NULL, NULL);
}

void draw_minimap(t_db *data)
{
	int x;
	int y;
	int k;

	y = -1;
	SDL_SetRenderDrawColor(data->sdl.renderer, 0, 0, 255, 255);
	SDL_Rect rect = create_rect(data->map.fill, data->map.fill, data->player.x * data->map.fill, data->player.y * data->map.fill);
	draw_rect(rect, (cl_float4){0, 0, 255, 255}, data->sdl.renderer);
	while (++y < data->map.heg)
	{
		x = -1;
		k = y * data->map.fill * data->sdl.width;
		while (++x < data->map.len)
		{
			if (data->map.cell[y * data->map.len + x].wall)
			{
				SDL_Rect rect = create_rect(data->map.fill, data->map.fill,
											k % data->sdl.width, k / data->sdl.width);
				draw_rect(rect, (cl_float4){0, 0, 0, 255}, data->sdl.renderer);
			}
			k += data->map.fill;
		}
	}
}
