#include "../includes/wolf3d.h"

int main(int ac, char **av)
{
	t_db *data;

	if (ac != 2)
		error(1);
	data_init(av[1], data);
}
