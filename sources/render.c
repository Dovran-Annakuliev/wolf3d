#include "../includes/wolf3d.h"

void 		update_texture(SDL_Texture *texture, int width, int height)//, int *r)
{
	Uint32				*pixels;
	int					pitch;
	SDL_PixelFormat		*format;

	SDL_LockTexture(texture, NULL, (void**)&pixels, &pitch) != 0 ? error(4) : 0;
	format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
	for (int i = 0; i < height * width ; ++i)
//	{
//		if (r[i] == 0)
//			pixels[i] = SDL_MapRGBA(format, 0, 0, 0, 0);
//		else
			pixels[i] = SDL_MapRGBA(format, 255, 255, 255, 0);
//	}
	SDL_UnlockTexture(texture);
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
