#include "../includes/wolf3d.h"

static int	ft_strlen_split(char const *s, char c)
{
	int i;
	int len;

	i = -1;
	len = 0;
	while (s[++i])
		if (s[i] != c && (!s[i + 1] || s[i + 1] == c))
			len++;
	return (len);
}

static void	set_status(t_db *data, int k, char *status, int i, int j)
{
	data->map.map[k].status = '0';
	if (ft_strcmp(status, "1") == 0)
		data->map.map[k].wall = 1;
	else if (ft_strcmp(status, "0") == 0)
		data->map.map[k].wall = 0;
	else
	{
		data->map.map[k].wall = 0;
		if (ft_strcmp(status, "A") == 0)
			data->map.map[k].status = 'A';
		else if (ft_strcmp(status, "E") == 0)
			data->map.map[k].status = 'E';
		else if (ft_strcmp(status, "P") == 0)
			data->map.map[k].status = 'P';
		else if (ft_strcmp(status, "W") == 0)
			data->map.map[k].status = 'W';
		else if (ft_strcmp(status, "M") == 0)
			data->map.map[k].status = 'M';
		else
			error(2);
	}
//	ft_printf("[%d][%d]:\tstatus = %c\t", i, j, data->map.map[k].status);
//	ft_printf("wall = %d\n", data->map.map[k].wall);
}

static void	ft_split(t_db *data, char *line, int i)
{
	int		k;
	int		j;
	char	**array;

	j = -1;
	k = i * data->map.len;
	array = ft_strsplit(line, ' ');
	while (array[++j])
	{
//		ft_printf("%s ", array[j]);
		set_status(data, k, array[j], i, j);
		data->map.map[k].x = j;
		data->map.map[k].y = i;
		free(array[j]);
		k++;
	}
	free(array);
}

static void	read_size(int fd, char *line, t_db *data)
{
	while (get_next_line(fd, &line))
	{
		if (!data->map.len)
			data->map.len = ft_strlen_split(line, ' ');
		if (data->map.len != ft_strlen_split(line, ' '))
			error(2);
		data->map.heg++;
		free(line);
	}
}

void		read_arg(char *source, t_db *data)
{
	char	*line;
	int		i;
	int		fd;

	line = NULL;
	data->map.heg = 0;
	data->map.len = 0;
	if (((fd = open(source, O_RDONLY)) < 0)
		|| ((read(fd, line, 0)) < 0))
		error(1);
	read_size(fd, line, data);
	data->map.map = (t_point *)malloc(sizeof(t_point)
			* data->map.heg * data->map.len);
	close(fd);
	i = -1;
	fd = open(source, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		ft_split(data, line, ++i);
		ft_strdel(&line);
	}
	free(line);
	close(fd);
}

/*
** 0 - Empty
** 1 - Wall
** A - Ammo
** E - Enemy
** P - Player
** W - Weapon
** M - Medicine
*/
