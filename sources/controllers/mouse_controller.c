#include "../../includes/wolf3d.h"

void		mouse_controller(SDL_Event *event, t_db *data)
{
	int x;
	int y;

	if (event)
		;
	SDL_GetMouseState(&x, &y);
	ft_printf("x = %d, y = %d\n", x, y);
}
