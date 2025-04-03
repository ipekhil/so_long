#ifndef SO_LONG_H
# define SO_LONG_H

# include "./libft/libft.h"
# include "./get_next_line/get_next_line.h"
# include "./printf/printf.h"
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
#include "mlx/mlx.h"

typedef struct s_textures
{
    void    *player;
    void	*wall;
	void	*floor;
	void	*exit;
	void	*collect;
}   t_textures;

typedef struct s_game
{
    void    *mlx;
    void    *win;
    char    **map;
    int     height;
    int     width;
    int     player_x;
    int     player_y;
    int     moves;
    int     collectibles;
    int     collected;
    int     count;
    int     exit_reached;
    t_textures  textures;

}	t_game;

int	handle_error(char *msg, char **map, int exit_mode);
void	initialize_game_values(t_game *game);
int	parse_map(char	*filename, t_game	*game);
int	map_height(char	*filename);
char	**read_map(char	*filename, int	height);
int	handle_exit(void *parameter);
void	free_map(char **map);
int	validate_map(t_game *game);
int	validate_walls(t_game *game);
void	init_textures(t_game *game);
void    render(t_game *game);
void    move_player(t_game *game, int dx, int dy);
void	exit_game(t_game *game);
int key_hook(int keycode, t_game *game);


char	**copy_map(t_game *game);
void    flood_fill(t_game *game, char **map, int row, int col);
void    flood_fill_controller(t_game *game);
#endif