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

static void	split(t_db *data, char *line, int i)
{
	int		k;
	int		j;
	char	**array;

	j = -1;
	k = i * data->map.len;
	array = ft_strsplit(line, ' ');
	while (array[++j])
	{
		if (ft_strcmp(array[j], "1") == 0)
			data->map.map[k].status = '1';
		else if (ft_strcmp(array[j], "A") == 0)
			data->map.map[k].status = 'A';
		else if (ft_strcmp(array[j], "E") == 0)
			data->map.map[k].status = 'E';
		else if (ft_strcmp(array[j], "P") == 0)
			data->map.map[k].status = 'P';
		else if (ft_strcmp(array[j], "W") == 0)
			data->map.map[k].status = 'W';
		else if (ft_strcmp(array[j], "M") == 0)
			data->map.map[k].status = 'M';
		else
			data->map.map[k].status = '0';
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

void read_arg(char *source, t_db *data)
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
		split(data, line, ++i);
		ft_strdel(&line);
	}
	free(line);
	close(fd);
}
