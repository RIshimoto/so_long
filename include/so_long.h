#ifndef SO_LONG_H 
# define SO_LONG_H

# include "mlx.h"
# include "key_macos.h"
# include "get_next_line.h"
# include "libft.h"
# include <math.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>

# define SUCESS 1
# define END 0
# define ERROR -1
# define X_EVENT_KEY_PRESS 2
# define X_EVENT_KEY_RELEASE 3
# define X_EVENT_KEY_EXIT 33
# define BLACK	0x00000000
# define WHITE	0x00FFFFFF
# define RED	0x00FF0000
# define GREEN	0x0000FF00
# define BLUE	0x000000FF
# define TILE_SIZE 35
# define QSIZE		1000000
# define HASHSIZE	299993

typedef	struct		s_state
{
	int				x;
	int				y;
	struct s_state	*hash_link;
}					t_state;

typedef struct s_img {
	void *img;
	int *addr;
	int bpp;
	int size_l;
	int endian;
	int width;
	int height;
}				t_img;

typedef struct s_game {
	void *mlx;
	void *win;
	t_img img;
	t_img texture[5];
	char **map;
	int map_col;
	int map_row;
	int movement;
	int	p_posx;
	int	p_posy;
}			t_game;

void fetch_game_data(char *file_name, t_game *p);
void fetch_each_line(int fd, t_game *p);
void check_map_closed(t_game *p);
void check_map_char(t_game *p);
int get_next_line(int fd, char **line);

#endif
