#include "../includes/wolf3d.h"

void fill_cell(Uint32 *pixels, SDL_PixelFormat *format, t_cell cell, int width)
{
	int i;
	int j;

	i = cell.y - cell.fill;
	while (i < cell.y + cell.fill)
	{
		j = cell.x - cell.fill;
		while (j < cell.x + cell.fill)
		{
			pixels[i * width + j] = SDL_MapRGBA(format, 0, 0, 200, 0);
			j++;
		}
		i++;
	}
}

void 		update_texture(t_db *data)//, int *r)
{
	Uint32				*pixels;
	SDL_PixelFormat		*format;
	int					pitch;
	int i;
	int j;
	int x;
	int y;
	int k;

//	if (SDL_LockTexture(data->sdl.texture, NULL, (void**)&pixels, &pitch) != 0)
//		error(TEXTURE_LOCK_ERROR, SDL_GetError());
//	format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	y = -1;
	k = 0;
	while (++y < data->map.heg)
	{
		x = -1;
		while (++x < data->map.len)
		{
			if (data->map.cell[y * data->map.len + x].wall)
			{
				SDL_Rect rect;
				rect.h = 64;
				rect.w = 64;
				rect.x = k % data->sdl.width;
				rect.y = k / data->sdl.width;
				SDL_SetRenderDrawColor(data->sdl.renderer, 150, 0, 0, 0);
				SDL_RenderFillRect(data->sdl.renderer, &rect);
			}
			k += 64;
			if (k > data->map.len * 64)
				k += data->sdl.width;
		}
	}
//	SDL_UnlockTexture(data->sdl.texture);
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
