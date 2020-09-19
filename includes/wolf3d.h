#ifndef WOLF3D_WOLF3D_H
#define WOLF3D_WOLF3D_H

#ifdef __APPLE__
# include <OpenGL/gl.h>
# include <OpenCL/opencl.h>
#include "../SDL2.framework/Headers/SDL.h"
#include "../SDL2_image.framework/Headers/SDL_image.h"
#else
//# include <GL/opengl.h>
# include <CL/opencl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include "../libft/includes/libft.h"
#include "error_codes.h"


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

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
	int		fill;
}				t_map;

typedef struct	s_plr
{
	int x;
	int y;
	float pov;
	float fov;
	int x_ms;
	int y_ms;
}				t_plr;

typedef struct	s_sdl
{
	SDL_Window		*window;
	SDL_Renderer	*renderer;
	SDL_Texture		*texture;
	int				width;
	int				height;
}				t_sdl;

typedef struct			s_cl
{
	cl_platform_id		platform_id;
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	char				**kernel_source;
	int					count;
	size_t				dim;
	size_t				global_size[1];
}						t_cl;

typedef struct	s_db
{
	t_map	map;
	t_sdl	sdl;
	t_cl	cl;
	t_plr	player;
}				t_db;

/*
** ---init functions---
*/

t_db 			*data_init(char *source);
void			read_arg(char *source, t_db *data);
void			create_lvl(t_db *data);

/*
** ---rendering functions---
*/

void 			update_texture(t_db *data);
int				*render(t_cl *cl, int w, int h);
void			player_present(t_db *data);
SDL_Rect		create_rect(int h, int w, int x, int y);
void 	draw_rect(SDL_Rect rect, cl_float4 color, SDL_Renderer *renderer);
void draw_minimap(t_db *data);
void create_background(t_db *data);

/*
** ---controls---
*/

void					controller(SDL_Event *event, t_db *data);
void					keyboard_controller(SDL_Event *event, t_db *data);
void					mouse_controller(SDL_Event *event, t_db *data);

/*
** ---utils---
*/

void			error(int er, const char *message);
void 			close_wolf(t_db *data);

//del
void print_rect(SDL_Rect rect);

#endif
