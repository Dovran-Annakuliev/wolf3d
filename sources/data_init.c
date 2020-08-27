#include "../includes/wolf3d.h"

void	data_init(char *source, t_db *data)
{
	if (!(data = (t_db*)malloc(sizeof(t_db))))
		error(0);
	read_arg(source, data);

	int i = 0;

	while (i < data->map.heg)
	{
		int j = 0;
		while (j < data->map.len)
		{
			write(1, &data->map.map[i * data->map.len + j], 1);
			write(1, " ", 1);
		}
		write(1, "\n", 1);
		i++;
	}
}
