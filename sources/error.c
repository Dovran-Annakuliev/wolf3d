#include "../includes/wolf3d.h"

void error(int er)
{
	if (er == 1)
		ft_printf("invalid number arguments\n");
	else if (er == 2)
		ft_printf("invalid map\n");
	exit(0);
}
