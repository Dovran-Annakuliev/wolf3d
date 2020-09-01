#ifndef WOLF3D_WOLF3D_H
#define WOLF3D_WOLF3D_H

#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenCL/opencl.h>
#else
# include <GL/opengl.h>
# include <CL/opencl.h>
#endif

#include "../libft/includes/libft.h"
#include "../SDL2.framework/Headers/SDL.h"
#include "../SDL2_image.framework/Headers/SDL_image.h"
#include "error_codes.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct	s_point
{
	int x;
	int y;
	int wall;
	char status;
}				t_cell;

typedef struct	s_map
{
	t_cell	*cell;
	int		len;
	int		heg;
}				t_map;

typedef struct	s_plr
{
	int x;
	int y;
	int pov;
	int fov;
}				t_plr;

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	int				width;
	int				height;
}				t_sdl;

typedef struct	s_cl
{

} t_cl;

typedef struct	s_db
{
	t_map	map;
	t_sdl	sdl;
	t_cl	cl;
}				t_db;

void			error(int er, char *message);
void 			close_wolf(t_db *data);

t_db 			*data_init(char *source);//, t_db *data);
void			read_arg(char *source, t_db *data);

void 			update_texture(SDL_Texture *texture, int width, int height);//, int *r);
int				*render(t_cl *cl, int w, int h);

#endif
