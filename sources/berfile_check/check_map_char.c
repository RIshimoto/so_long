#include "../../include/so_long.h"

static void		check_map_start_pos(t_game *p)
{
	bool	find_start_pos;
	int		i;
	int		j;

	find_start_pos = false;
	i = -1;
	while (++i < p->map_col)
	{
		j = -1;
		while (++j < p->map_row)
		{
			if (p->map[i][j] == 'P')
			{
				if (find_start_pos)
				{
					perror("Error\nMap must have only one start pos\n");
					exit(EXIT_FAILURE);
				}
				find_start_pos = true;
				p->p_posx = i;
				p->p_posy = j;
			}
		}
	}
	if (!find_start_pos)
	{
		perror("Error\nMap must have at least one starting position\n");
		exit(EXIT_FAILURE);
	}
}

static void		check_map_irregular_char(t_game *p)
{
	int		i;
	int		j;
	bool	findC;
	bool	findE;

	findC = false;
	findE = false;
	i = -1;
	while (++i < p->map_col)
	{
		j = -1;
		while (++j < p->map_row)
		{
			if (!(ft_strchr("PEC01", p->map[i][j])))
			{
				perror("Error\nInvalid char\n");
				exit(EXIT_FAILURE);
			}
			else if (p->map[i][j] == 'C')
				findC = true;
			else if (p->map[i][j] == 'E')
				findE = true;
		}
	}
	if (!findC || !findE)
	{
		perror("Error\n Map must have at least one exit, one collectible\n");
		exit(EXIT_FAILURE);
	}
}

void			check_map_char(t_game *p)
{
	check_map_start_pos(p);
	check_map_irregular_char(p);
}
