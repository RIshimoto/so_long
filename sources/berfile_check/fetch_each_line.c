#include "../../include/so_long.h"

/*
static void		map_resize(t_game *p)
{
	char	**m;
	int		i;
	int		j;

	m = (char **)malloc(sizeof(char *) * p->map_);
	i = -1;
	while (++i < p->map_height)
	{
		m[i] = (char *)malloc(sizeof(char) * p->map_width);
		ft_memset(m[i], ' ', p->map_width);
		j = 0;
		while (p->map[i][j] != '\0')
		{
			m[i][j] = p->map[i][j];
			j++;
		}
		free(p->map[i]);
	}
	free(p->map);
	p->map = m;
}
*/

static char		**store_map(char *add_line, t_game *p)
{
	char	**new;
	int		row;
	int		i;

	new = (char **)malloc(sizeof(char *) * (p->map_row + 2));
	i = -1;
	while (++i < p->map_col)
		new[i] = p->map[i];
	new[i++] = add_line;
	new[i] = NULL;
	p->map_col++;
	row = ft_strlen(add_line);
	free(p->map);
	if (p->map_row == -1)
		p->map_row = row;
	else if (p->map_row != row)
	{
		perror("Error\nNot rectangular!\n");
		i = 0;
		while (new[i] != NULL)
		{
			free(new[i]);
			i++;
		}
		free(new);
		exit(1);
	}
	return (new);
}

void			fetch_each_line(int fd, t_game *p)
{
	char		*line;
	int			gnl;

	while (0 < (gnl = get_next_line(fd, &line)))
	{
		//check_identify(line, p);
		p->map = store_map(line, p);
	}
	free(line);
	//map_resize(p);
}
