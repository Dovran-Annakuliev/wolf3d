#include "../includes/wolf3d.h"
//
//void draw_fov(t_db *data, float angle, int i)
//{
//	float view_line;
//	float x;
//	float y;
//	int k;
//
//	view_line = 0;
//	while (view_line <= 20)
//	{
//		x = data->player.x + view_line * cosf(angle);
//		y = data->player.y + view_line * sinf(angle);
//		k = (int)x + (int)y * data->map.len;
//		if (data->map.cell[k].wall != 0)
//			break;
//		view_line += 0.05f;
//	}
//	SDL_SetRenderDrawColor(data->sdl.renderer, 0, 0, 255, 255);
//	SDL_RenderDrawLineF(data->sdl.renderer, data->player.x * data->map.fill,
//					 data->player.y * data->map.fill, x * data->map.fill, y * data->map.fill);
//	SDL_SetRenderDrawColor(data->sdl.renderer, 255, 0, 0, 255);
//
//	unsigned line2 = data->sdl.height / (view_line * cosf(angle - data->player.pov * (float)M_PI / 180)) / 2;
//	SDL_RenderDrawLineF(data->sdl.renderer, i, data->sdl.height / 2 - line2, i, data->sdl.height / 2 + line2);
//}
//
//void player_present(t_db *data)
//{
//	float angle;
//	float step;
//	float fin;
//
//	angle = (data->player.pov - data->player.fov / 2) * (float)M_PI / 180;
//	step = (data->player.fov * (float)M_PI / 180) / data->sdl.width;
//	fin = (data->player.pov + data->player.fov / 2) * (float)M_PI / 180;
//
//	int i = 0;
//	while (angle <= fin)
//	{
//		draw_fov(data, angle, i++);
//		angle += step;
//	}
//}

static int		check_wall(int x, int y, t_db *data)
{
	int k;
	k = x + y * data->map.len;
	if (data->map.cell[k].wall == 0)
		return (0);
	return (1);
}

static float	horizontal_intersect(int i, t_db *data, float angle)
{
	int is_up;
	int dist;
	t_cell A;
	t_cell X;

	is_up = angle < 0 || (angle > 180 && angle < 360) ? 1 : 0;
	if (is_up)
		A.y = (data->player.y / data->map.fill) * data->map.fill - 1;
	else
		A.y = (data->player.y / data->map.fill) * data->map.fill + data->map.fill;
	A.x = (int)(data->player.x + (data->player.y - A.y)/tan(angle * M_PI / 180));
	if (!check_wall(A.x / data->map.fill, A.y / data->map.fill, data))
	{
		X.y = is_up ? -data->map.fill : data->map.fill;
		X.x = (int) (data->map.fill / tan(angle * M_PI / 180));
		dist = 0;
		while (dist < 20)
		{
			A.x = A.x + X.x;
			A.y = A.y + X.y;
			if (check_wall(A.x / data->map.fill, A.y / data->map.fill, data))
				break;
			dist++;
		}
	}
	return (abs(data->player.x - A.x) / cos(angle * M_PI / 180));
}

static float		vertical_intersect(int i, t_db *data, float angle)
{
	int is_right;
	int dist;
	t_cell B;
	t_cell X;

	is_right = angle < 90 || (angle > 270 && angle < 450) ? 1 : 0;
	if (is_right)
		B.x = (data->player.x / data->map.fill) * data->map.fill + data->map.fill;
	else
		B.x = (data->player.x / data->map.fill) * data->map.fill - 1 ;
	B.y = (int)(data->player.y + (data->player.x - B.x)/tan(angle * M_PI / 180));
	if (!check_wall(B.x / data->map.fill, B.y / data->map.fill, data))
	{
		X.x = is_right ? data->map.fill : -data->map.fill;
		X.y = (int) (data->map.fill * tan(angle * M_PI / 180));
		dist = 0;
		while (dist < 10)
		{
			B.x = B.x + X.x;
			B.y = B.y + X.y;
			if (check_wall(B.x / data->map.fill, B.y / data->map.fill, data))
				break;
			dist++;
		}
	}
	return (abs(data->player.x - B.x) / cos(angle * M_PI / 180));
}

void		cast_rays(t_db *data)
{
	float min = data->player.pov - data->player.fov / 2;
	float max = data->player.pov + data->player.fov / 2;
	float delta = data->player.fov / (float)data->sdl.width;
	int dist_to_proj_plane = (data->sdl.width / 2) / SDL_tanf(data->player.fov/2 * M_PI / 180);

	int i = 0;
	float horiz_dist;
	float vert_dist;
	float res_dist;
	unsigned wall_height;
	while (min <= max)
	{
		horiz_dist = horizontal_intersect(i, data, min);
		vert_dist = vertical_intersect(i, data, min);
		res_dist = horiz_dist < vert_dist ? horiz_dist : vert_dist;
		wall_height = data->map.fill / res_dist * dist_to_proj_plane;
		SDL_RenderDrawLineF(data->sdl.renderer, i, data->sdl.height / 2 - wall_height / 2, i, data->sdl.height / 2 + wall_height / 2 );
		min += delta;
		i++;
	}
}
