#include "../include/so_long.h"

void swap(char *a, char *b)
{
	char tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

static int closer(t_game *game)
{
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

static int key_press(int key, t_game *game)
{
	int posnx;
	int posny;

	posnx = game->p_posx;
	posny = game->p_posy;
	if (key == K_ESC)
		closer(game);
	if (key == K_LEFT || key == K_A)
		posny = game->p_posy - 1;
	if (key == K_UP || key == K_W)
		posnx = game->p_posx - 1;
	if (key == K_RIGHT || key == K_D)
		posny = game->p_posy + 1;
	if (key == K_DOWN || key == K_S)
		posnx = game->p_posx + 1;
	if (game->map[posnx][posny] != '1')
	{
		if (game->map[posnx][posny] == 'C')
			game->map[posnx][posny] = '0';
		else if (game->map[posnx][posny] == 'E')
			closer(game);
		swap(&game->map[posnx][posny], &game->map[game->p_posx][game->p_posy]);
		game->p_posx = posnx; 
		game->p_posy = posny; 
		game->movement++;
		printf("%d\n\033[1A", game->movement);
	}
	return 0;
}


void draw_texture(t_game *game, int x, int y, t_img *texture)
{
	int i, j;
	int rg, lf;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	i = -1;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
		{
			lf = (i + y) * game->map_row * TILE_SIZE + (j + x);
			rg = i * TILE_SIZE + j;
			game->img.addr[lf] = texture->addr[rg];
		}
	}
}

void draw_rectangle(t_game *game, int x, int y, int color)
{
	int i, j;
	int width;

	x *= TILE_SIZE;
	y *= TILE_SIZE;
	width = game->map_row * TILE_SIZE;
	i = 0;
	while (i < TILE_SIZE)
	{
		j = 0;
		while (j < TILE_SIZE)
		{
			game->img.addr[(y + i) * width+ (x + j)] = color; 
			j++;
		}
		i++;
	}
}

void draw_rectangles(t_game *game)
{
	int i;
	int j;

	i = -1;
	while(++i < game->map_col)
	{
		j = -1;
		while (++j < game->map_row)
		{
			if (game->map[i][j] == '0')
				draw_texture(game, j, i, &game->texture[0]);
			else if (game->map[i][j] == '1')
				draw_texture(game, j, i, &game->texture[1]);
			else if (game->map[i][j] == 'C')
				draw_texture(game, j, i, &game->texture[2]);
			else if (game->map[i][j] == 'E')
				draw_texture(game, j, i, &game->texture[3]);
			else if (game->map[i][j] == 'P')
				draw_texture(game, j, i, &game->texture[4]);
		}
	}
}

static int main_loop(t_game *game)
{
	draw_rectangles(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0); 
	return 0;
}

void  load_texture(t_game *game, t_img *texture, char *path)
{
	t_img img;
	int i;
	int j;
	int index;
	double Sx, Sy;

	texture->addr = malloc(sizeof(int) * TILE_SIZE * TILE_SIZE);
	img.img = mlx_xpm_file_to_image(game->mlx, path, &img.width, &img.height);
	img.addr = (int*)mlx_get_data_addr(img.img, &img.bpp, &img.size_l, &img.endian); 
	Sx = (double)TILE_SIZE / img.width;
	Sy = (double)TILE_SIZE / img.height;
	i = -1;
	while (++i < TILE_SIZE)
	{
		j = -1;
		while (++j < TILE_SIZE)
		{
			index = (int)floor(i/Sy)*img.width+floor(j/Sx); 
			texture->addr[i * TILE_SIZE + j] = img.addr[index];
		}
	}
}

void game_init(t_game *game)
{
	int width, height;

	width = game->map_row * TILE_SIZE;
	height = game->map_col * TILE_SIZE;

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, width, height, "so_long");
	game->img.img = mlx_new_image(game->mlx, width, height);
	game->img.addr = (int*)mlx_get_data_addr(game->img.img, &game->img.bpp, &game->img.size_l, &game->img.endian);
	load_texture(game, &game->texture[0], "./textures/colorstone.xpm");//0
	load_texture(game, &game->texture[1], "./textures/wood.xpm");// 1 
	load_texture(game, &game->texture[2], "./textures/takara.xpm");// C
	load_texture(game, &game->texture[3], "./textures/warp_hole.xpm");// E
	load_texture(game, &game->texture[4], "./textures/dolphin.xpm");// P
}


int main(int argc, char **argv)
{
	t_game 		game;

	if (argc > 3)
	{
		ft_putstr_fd("Error\nToo many argument\n", 2); 
		exit(EXIT_FAILURE);
	}
	fetch_game_data(argv[1], &game);
	game_init(&game);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 1L<<0, &key_press, &game);
	mlx_hook(game.win, X_EVENT_KEY_EXIT, 1L<<17, &closer, &game);
	mlx_loop_hook(game.mlx, &main_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
