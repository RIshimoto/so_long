#include "../../include/so_long.h"

static void		check_file_name(char *file, char *extention)
{
	int i;
	int	len;

	len = ft_strlen(file);
	i = -1;
	while (++i < 4)
	{
		if (file[len - i - 1] == extention[3 - i])
			continue;
		perror("Error\nwrong file name\n");
		exit(EXIT_FAILURE);
	}
	return;
}

static void		init(t_game *p)
{
	p->map = (char **)malloc(sizeof(char*) * 1);
	p->map[0] = NULL;
	p->map_col = 0;
	p->map_row = -1;
	p->p_posx = -1;
	p->p_posy = -1;
	p->movement = 0;
}

void			fetch_game_data(char *file_name, t_game *p)
{
	int fd;

	if ((fd = open(file_name, O_RDONLY)) < 0)
	{
		perror("Error\n");
		exit(EXIT_FAILURE);
	}
	init(p);
	check_file_name(file_name, ".ber");
	fetch_each_line(fd, p);
	check_map_char(p);
	check_map_closed(p);
	close(fd);
	/*
	if (!p->valid)
	{
		all_free(p);
		exit(0);
	}
	*/
}
