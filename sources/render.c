#include "../includes/wolf3d.h"

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

void 		update_texture(t_db *data)//, int *r)
{
	int x;
	int y;
	int k;

	create_background(data);

	y = -1;
	k = 0;
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
//				ft_printf("[%d],[%d] x = %d, y = %d, k = %d\n", y, x, rect.y, rect.x, k);
			}
//			ft_printf("[%d],[%d] k = %d\n", y, x, k);
			k += data->map.fill;
		}
	}

}


//int		*render(t_cl *cl, int w, int h)
//{
//	cl_mem		output_buffer;
//	int		*res;
//	t_sphere	s;
//	float 		fov;
//
//	fov = 120.0f;
//	s = new_sphere(new_vector3(0.0f, 0.0f, -15.0f), 10.0f, new_material(new_vector3(240, 180, 50)));
//	if (!(res = (int*)malloc(sizeof(int) * w * h)))
//		error(MALLOC_ERROR, "renderer malloc error");
//	output_buffer = clCreateBuffer(cl->context, CL_MEM_WRITE_ONLY, sizeof(int) * w * h, NULL, NULL);
//	clSetKernelArg(cl->kernel, 0, sizeof(float), &fov);
//	clSetKernelArg(cl->kernel, 1, sizeof(t_sphere), &s);
//	clSetKernelArg(cl->kernel, 2, sizeof(cl_mem), &output_buffer);
//	clEnqueueNDRangeKernel(cl->queue, cl->kernel, cl->dim, NULL,
//						   cl->global_size, NULL, 0, NULL, NULL);
//	clFinish(cl->queue);
//	clEnqueueReadBuffer(cl->queue, output_buffer, CL_TRUE, 0, sizeof(int) * w * h,
//						res, 0, NULL, NULL);
//	clFinish(cl->queue);
//	clReleaseMemObject(output_buffer);
//	return (res);
//}
