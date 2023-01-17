#include "../../include/so_long.h"

static int		hash(int x, int y)
{
	int		i;
	int		hash;
	int		y_keta;
	char	*tmp;

	tmp = ft_itoa(y);
	y_keta = (int)ft_strlen(tmp);
	free(tmp);
	hash = x;
	i = -1;
	while (++i < y_keta)
	{
		hash *= 10;
		hash %= HASHSIZE;
	}
	hash += y % HASHSIZE;
	hash %= HASHSIZE;
	return (hash);
}

static t_list	*create_lst(int x, int y, t_state *link)
{
	t_state *next;

	next = (t_state *)malloc(sizeof(t_state) * 1);
	next->x = x;
	next->y = y;
	next->hash_link = link;
	return (ft_lstnew(next));
}

static bool		equal(int nx, int ny, t_state *start)
{
	while (start != NULL)
	{
		if (start->x == nx && start->y == ny)
			return (true);
		start = start->hash_link;
	}
	return (false);
}

static int		move(t_game *p, int nx, int ny, t_list **head)
{
	static t_state	*hash_table[HASHSIZE];
	t_list			*lst;
	int				h;

	if ((nx < 0 || nx > p->map_col) || (ny < 0 || ny >= p->map_row))
	{
		perror("Error\nOpened map\n");
		exit(EXIT_FAILURE);
	}
	if (p->map[nx][ny] == '1')
		return (0);
	h = hash(nx, ny);
	if (equal(nx, ny, hash_table[h]))
		return (0);
	lst = create_lst(nx, ny, hash_table[h]);
	hash_table[h] = (t_state*)lst->content;
	(*head)->next = lst;
	*head = lst;
	return (1);
}

void			check_map_closed(t_game *p)
{
	int		queue;
	t_list	*head;
	t_list	*tail;
	t_list	*queue_top;
	t_state	*now;

	queue_top = create_lst(-1, -1, NULL);
	tail = queue_top;
	head = queue_top;
	queue = move(p, p->p_posx, p->p_posy, &head);
	while (queue-- > 0)
	{
		tail = tail->next;
		now = (t_state *)tail->content;
		queue += move(p, now->x + 1, now->y, &head);
		queue += move(p, now->x, now->y + 1, &head);
		queue += move(p, now->x - 1, now->y, &head);
		queue += move(p, now->x, now->y - 1, &head);
	}
	ft_lstclear(&queue_top, free);
}
